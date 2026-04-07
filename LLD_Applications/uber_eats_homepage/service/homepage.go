package service

import (
	"context"
	"log"
	"uber_eats_homepage/dto"
	"uber_eats_homepage/interfaces"
	"uber_eats_homepage/model"

	"github.com/mmcloughlin/geohash"
)

type homepageService struct {
	repo  interfaces.RestaurantRepository
	cache interfaces.GeoCache
}

func NewHomepageService(repo interfaces.RestaurantRepository, cache interfaces.GeoCache) interfaces.HomepageService {
	return &homepageService{
		repo:  repo,
		cache: cache,
	}
}

// AddRestaurant Creates and saves a restaurant and updates Geo Cache.
func (s *homepageService) AddRestaurant(ctx context.Context, req dto.AddRestaurantRequest) (*model.Restaurant, error) {
	// Generate base Geohash
	gHash := EncodeGeohash(req.Lat, req.Lng)
	
	restaurant := &model.Restaurant{
		Name:         req.Name,
		Lat:          req.Lat,
		Lng:          req.Lng,
		Geohash:      gHash,
		Cuisine:      req.Cuisine,
		Rating:       req.Rating,
		DeliveryTime: req.DeliveryTime,
	}

	if err := s.repo.Create(ctx, restaurant); err != nil {
		return nil, err
	}

	// Update Redis Geo Cache
	gPrefix := gHash[:GeohashPrecision]
	if err := s.cache.AddRestaurantToGeoCache(ctx, gPrefix, restaurant.ID.String()); err != nil {
		log.Printf("Failed to update geo cache for restaurant %s: %v", restaurant.ID, err)
		// We shouldn't fail the request completely if cache misses, it's just degraded performance or eventually consistent.
	}

	// For demonstration, arbitrarily make highly rated new restaurants trending in their geohash chunk
	if req.Rating >= 4.5 {
		_ = s.cache.AddTrending(ctx, gPrefix, restaurant.ID.String())
	}

	return restaurant, nil
}

// GetHomepage fetches nearby restaurants, applies distance filter, and pulls trending.
func (s *homepageService) GetHomepage(ctx context.Context, lat, lng float64) (*dto.HomepageResponse, error) {
	// 1. Get neighboring geohash prefixes (central + 8 neighbors)
	// GeohashPrecision of 5 implies ~4.9x4.9km boxes.
	prefixes := GetNeighboringPrefixes(lat, lng, GeohashPrecision)

	// 2. Query Redis for cached restaurants in these prefixes
	restaurantIDs, err := s.cache.GetRestaurantsByGeoPrefixes(ctx, prefixes)
	if err != nil {
		log.Printf("Redis GetRestaurantsByGeoPrefixes error: %v. Falling back to DB.", err)
	}

	var candidates []model.Restaurant
	var dbHitRequired bool

	// If redis returns empty, it could be a cold start. We fallback to DB scattering across shards.
	if len(restaurantIDs) > 0 {
		candidates, err = s.repo.GetByIDs(ctx, restaurantIDs)
		if err != nil {
			log.Printf("DB GetByIDs failed: %v", err)
			dbHitRequired = true
		}
	} else {
		dbHitRequired = true
	}

	// Fallback mechanism (Cache Miss / Empty)
	if dbHitRequired {
		candidates, err = s.repo.GetByGeohashPrefixes(ctx, prefixes)
		if err != nil {
			return nil, err
		}
		// Populate Cache asynchronously if not empty
		if len(candidates) > 0 {
			go func() {
				bgCtx := context.Background()
				for _, c := range candidates {
					prefix := c.Geohash[:GeohashPrecision]
					_ = s.cache.AddRestaurantToGeoCache(bgCtx, prefix, c.ID.String())
				}
			}()
		}
	}

	// 3. Post-Filter using Haversine calculation to ensure bounded precision.
	// Geohashes are rectangles, so neighbors include corners perfectly fine, but some points may be 
	// slightly over the MaxSearchRadiusKm from our exact point. Filter them dynamically.
	var nearby []model.Restaurant
	for _, c := range candidates {
		distance := Haversine(lat, lng, c.Lat, c.Lng)
		if distance <= MaxSearchRadiusKm {
			nearby = append(nearby, c)
		}
	}

	// 4. Fetch Trending (Pre-computed / Pre-cached in Redis)
	centerPrefix := geohash.EncodeWithPrecision(lat, lng, GeohashPrecision)
	trendingIDs, _ := s.cache.GetTrending(ctx, centerPrefix)
	var trending []model.Restaurant
	
	if len(trendingIDs) > 0 {
		tCand, _ := s.repo.GetByIDs(ctx, trendingIDs)
		// Usually trending might span a bit more, but we check distance anyway
		for _, t := range tCand {
			if Haversine(lat, lng, t.Lat, t.Lng) <= MaxSearchRadiusKm*2.0 { // wider net for trending
				trending = append(trending, t)
			}
		}
	} else {
		// Fallback to db
		trending, _ = s.repo.GetTrending(ctx, centerPrefix)
	}

	return &dto.HomepageResponse{
		Location:          centerPrefix, // Represent logical user area
		NearbyRestaurants: nearby,
		Trending:          trending,
	}, nil
}
