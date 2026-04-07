package repository

import (
	"context"
	"fmt"
	"uber_eats_homepage/interfaces"
	"time"

	"github.com/redis/go-redis/v9"
)

type RedisGeoCache struct {
	client *redis.Client
}

func NewRedisGeoCache(client *redis.Client) interfaces.GeoCache {
	return &RedisGeoCache{
		client: client,
	}
}

// AddRestaurantToGeoCache stores the restaurant in a Redis Set keyed by geohashPrefix.
func (c *RedisGeoCache) AddRestaurantToGeoCache(ctx context.Context, geohashPrefix, restaurantID string) error {
	key := fmt.Sprintf("geo:%s", geohashPrefix)
	return c.client.SAdd(ctx, key, restaurantID).Err()
}

// GetRestaurantsByGeoPrefixes fetches all restaurant IDs from multiple geohash prefixes.
func (c *RedisGeoCache) GetRestaurantsByGeoPrefixes(ctx context.Context, geohashPrefixes []string) ([]string, error) {
	var keys []string
	for _, p := range geohashPrefixes {
		keys = append(keys, fmt.Sprintf("geo:%s", p))
	}

	// SUnion gets unique members across all given sets
	return c.client.SUnion(ctx, keys...).Result()
}

// AddTrending adds a trending restaurant to a region.
func (c *RedisGeoCache) AddTrending(ctx context.Context, geohashPrefix string, restaurantID string) error {
	key := fmt.Sprintf("trending:%s", geohashPrefix)
	// Keeps only last 50
	pipe := c.client.Pipeline()
	pipe.LPush(ctx, key, restaurantID)
	pipe.LTrim(ctx, key, 0, 49)
	pipe.Expire(ctx, key, time.Hour*24)
	_, err := pipe.Exec(ctx)
	return err
}

// GetTrending returns trending restaurant IDs.
func (c *RedisGeoCache) GetTrending(ctx context.Context, geohashPrefix string) ([]string, error) {
	key := fmt.Sprintf("trending:%s", geohashPrefix)
	return c.client.LRange(ctx, key, 0, -1).Result()
}
