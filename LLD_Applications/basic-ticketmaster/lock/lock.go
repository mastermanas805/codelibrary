package lock

import (
	"time"

	"github.com/go-redsync/redsync/v4"
	"github.com/go-redsync/redsync/v4/redis/goredis/v9"
	"github.com/redis/go-redis/v9"
)

// Mutex is the interface for a distributed lock.
type Mutex interface {
	Lock() error
	Unlock() (bool, error)
}

// Factory creates distributed mutexes keyed by name.
type Factory interface {
	NewMutex(name string, options ...redsync.Option) Mutex
}

// --- Redis-backed implementation (production) ---

type RedisFactory struct {
	rs *redsync.Redsync
}

func NewRedisFactory(client *redis.Client) *RedisFactory {
	pool := goredis.NewPool(client)
	return &RedisFactory{rs: redsync.New(pool)}
}

func (f *RedisFactory) NewMutex(name string, options ...redsync.Option) Mutex {
	defaults := []redsync.Option{
		redsync.WithExpiry(5 * time.Second),
		redsync.WithTries(3),
		redsync.WithRetryDelay(50 * time.Millisecond),
	}
	opts := append(defaults, options...)
	return f.rs.NewMutex(name, opts...)
}

// --- No-op implementation (tests) ---

type NoOpMutex struct{}

func (m *NoOpMutex) Lock() error            { return nil }
func (m *NoOpMutex) Unlock() (bool, error)  { return true, nil }

type NoOpFactory struct{}

func NewNoOpFactory() *NoOpFactory { return &NoOpFactory{} }

func (f *NoOpFactory) NewMutex(_ string, _ ...redsync.Option) Mutex {
	return &NoOpMutex{}
}
