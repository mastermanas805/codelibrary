package repository

import (
	"context"
	"sync"
	"uber_eats_homepage/interfaces"
	"uber_eats_homepage/model"

	"gorm.io/gorm"
)

type ShardedRestaurantRepository struct {
	// In a real system, we'd map shard_id to a separate DB connection string.
	// We simulate this by having an array of DSNs or pointers to DB.
	shards []*gorm.DB
	numShards int
}

var (
	repoInstance *ShardedRestaurantRepository
	repoOnce     sync.Once
)

// NewShardedRestaurantRepository initializes the repository.
// For this LLD simulation, all shards point to the same DB but we demonstrate the routing logic.
func NewShardedRestaurantRepository(db *gorm.DB, numShards int) interfaces.RestaurantRepository {
	shards := make([]*gorm.DB, numShards)
	for i := 0; i < numShards; i++ {
		// Simulating different shards pointing to same db resource.
		shards[i] = db
	}
	return &ShardedRestaurantRepository{
		shards:    shards,
		numShards: numShards,
	}
}

// GetRestaurantRepository returns the singleton sharded repository.
func GetRestaurantRepository() interfaces.RestaurantRepository {
	if repoInstance == nil {
		panic("RestaurantRepository not initialized. Call NewShardedRestaurantRepository first.")
	}
	return repoInstance
}

// SetRestaurantRepository allows tests to override the singleton
func SetRestaurantRepository(repo interfaces.RestaurantRepository) {
	// Type assertion since the interface is what is returned normally, 
	// but we only set the instance internally.
	if r, ok := repo.(*ShardedRestaurantRepository); ok {
		repoInstance = r
	} else {
		// Mock assignments
		panic("Not supported to set non-sharded repo globally in this minimal structure.")
	}
}

// getShard routes the geohash to a specific shard. 
// A simple hash function on the prefix can determine the shard.
func (r *ShardedRestaurantRepository) getShard(geohash string) *gorm.DB {
	// Simple hash for sharding logic
	hash := 0
	for _, c := range geohash {
		hash += int(c)
	}
	return r.shards[hash%r.numShards]
}

func (r *ShardedRestaurantRepository) Create(ctx context.Context, restaurant *model.Restaurant) error {
	// Route based on Geohash prefix (e.g. length 5)
	shard := r.getShard(restaurant.Geohash[:5])
	restaurant.ShardID = hashShard(restaurant.Geohash[:5], r.numShards) // Just for record keeping

	return shard.WithContext(ctx).Create(restaurant).Error
}

func (r *ShardedRestaurantRepository) GetByGeohashPrefixes(ctx context.Context, prefixes []string) ([]model.Restaurant, error) {
	// Since each prefix might map to a different shard, we query the respective shard.
	var results []model.Restaurant
	var mu sync.Mutex
	var wg sync.WaitGroup

	errCh := make(chan error, len(prefixes))

	for _, prefix := range prefixes {
		wg.Add(1)
		go func(p string) {
			defer wg.Done()
			shard := r.getShard(p)
			var localRes []model.Restaurant
			// Search for prefix using LIKE
			if err := shard.WithContext(ctx).Where("geohash LIKE ?", p+"%").Find(&localRes).Error; err != nil {
				errCh <- err
				return
			}
			mu.Lock()
			results = append(results, localRes...)
			mu.Unlock()
		}(prefix)
	}

	wg.Wait()
	close(errCh)

	if len(errCh) > 0 {
		return nil, <-errCh // Return the first error
	}
	return results, nil
}

func (r *ShardedRestaurantRepository) GetTrending(ctx context.Context, geohash string) ([]model.Restaurant, error) {
	// Mock implementation. In reality, we might have a trending service that pre-computes this
	// and stores in a quick-access data store.
	shard := r.getShard(geohash[:5])
	var results []model.Restaurant
	if err := shard.WithContext(ctx).Where("geohash LIKE ?", geohash[:5]+"%").Order("rating desc").Limit(10).Find(&results).Error; err != nil {
		return nil, err
	}
	return results, nil
}

func (r *ShardedRestaurantRepository) GetByIDs(ctx context.Context, ids []string) ([]model.Restaurant, error) {
	// Scatter-gather query across shards
	var results []model.Restaurant
	
	// Since this is a simulation, we'll just query the first shard as it points to the same table.
	// In a real scattered shard, we execute query on all shards or maintain an index mapping ID -> Shard.
	if err := r.shards[0].WithContext(ctx).Where("id IN ?", ids).Find(&results).Error; err != nil {
		return nil, err
	}

	// For demonstration of scatter-gather missing, using a shortcut.
	return results, nil
}

func hashShard(key string, numShards int) int {
	hash := 0
	for _, c := range key {
		hash += int(c)
	}
	return hash % numShards
}
