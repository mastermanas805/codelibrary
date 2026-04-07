package interfaces

import (
	"context"

	"uber_eats_homepage/dto"
	"uber_eats_homepage/model"
)

type RestaurantRepository interface {
	Create(ctx context.Context, restaurant *model.Restaurant) error
	GetByGeohashPrefixes(ctx context.Context, prefixes []string) ([]model.Restaurant, error)
	GetTrending(ctx context.Context, geohash string) ([]model.Restaurant, error)
	GetByIDs(ctx context.Context, ids []string) ([]model.Restaurant, error)
}

type HomepageService interface {
	AddRestaurant(ctx context.Context, req dto.AddRestaurantRequest) (*model.Restaurant, error)
	GetHomepage(ctx context.Context, lat, lng float64) (*dto.HomepageResponse, error)
}

type GeoCache interface {
	AddRestaurantToGeoCache(ctx context.Context, geohashPrefix, restaurantID string) error
	GetRestaurantsByGeoPrefixes(ctx context.Context, geohashPrefixes []string) ([]string, error)
	AddTrending(ctx context.Context, geohashPrefix string, restaurantID string) error
	GetTrending(ctx context.Context, geohashPrefix string) ([]string, error)
}
