package main

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

type CacheEntry[V any] struct {
	value          V         // Immutable after construction
	expirationTime time.Time // Absolute expiration time
}

func NewCacheEntry[V any](value V, ttl time.Duration) *CacheEntry[V] {
	return &CacheEntry[V]{
		value: value,
		// time.Now() uses monotonic clock internally for duration comparisons
		// Go's time package handles monotonic time automatically
		expirationTime: time.Now().Add(ttl),
	}
}

func (e *CacheEntry[V]) Value() V {
	return e.value // Safe to call from any goroutine
}

func (e *CacheEntry[V]) IsExpired() bool {
	// time.Now().After() uses monotonic time for comparison
	// Simple comparison, no arithmetic needed at read time
	return time.Now().After(e.expirationTime)
}

type ThreadSafeCache[K comparable, V any] struct {
	cache    map[K]*CacheEntry[V]
	mu       sync.RWMutex
	stopChan chan struct{}
	wg       sync.WaitGroup
}

func NewThreadSafeCache[K comparable, V any](cleanupInterval time.Duration) *ThreadSafeCache[K, V] {
	c := &ThreadSafeCache[K, V]{
		cache:    make(map[K]*CacheEntry[V]),
		stopChan: make(chan struct{}),
	}

	if cleanupInterval > 0 {
		c.wg.Add(1)
		go c.cleanupLoop(cleanupInterval)
	}

	return c
}

func (c *ThreadSafeCache[K, V]) Get(key K) (V, bool) {
	c.mu.RLock()
	entry, exists := c.cache[key]
	c.mu.RUnlock()

	if !exists {
		var zero V
		return zero, false
	}

	if entry.IsExpired() {
		// Upgrade to write lock for removal
		c.mu.Lock()
		// Double-check after acquiring write lock
		if entry, exists := c.cache[key]; exists && entry.IsExpired() {
			delete(c.cache, key)
		}
		c.mu.Unlock()
		var zero V
		return zero, false
	}

	return entry.Value(), true
}

func (c *ThreadSafeCache[K, V]) Put(key K, value V, ttl time.Duration) {
	c.mu.Lock()
	c.cache[key] = NewCacheEntry(value, ttl)
	c.mu.Unlock()
}

func (c *ThreadSafeCache[K, V]) Remove(key K) bool {
	c.mu.Lock()
	_, existed := c.cache[key]
	delete(c.cache, key)
	c.mu.Unlock()
	return existed
}

func (c *ThreadSafeCache[K, V]) Size() int {
	c.mu.RLock()
	defer c.mu.RUnlock()
	return len(c.cache)
}

func (c *ThreadSafeCache[K, V]) cleanupLoop(interval time.Duration) {
	defer c.wg.Done()
	ticker := time.NewTicker(interval)
	defer ticker.Stop()

	for {
		select {
		case <-c.stopChan:
			return
		case <-ticker.C:
			c.cleanupExpiredEntries()
		}
	}
}

func (c *ThreadSafeCache[K, V]) cleanupExpiredEntries() {
	c.mu.Lock()
	defer c.mu.Unlock()

	for key, entry := range c.cache {
		if entry.IsExpired() {
			delete(c.cache, key)
		}
	}
}

func (c *ThreadSafeCache[K, V]) Shutdown() {
	close(c.stopChan)
	c.wg.Wait()

	c.mu.Lock()
	c.cache = make(map[K]*CacheEntry[V])
	c.mu.Unlock()
}

func main() {
	// Create cache with 1-second cleanup interval
	cache := NewThreadSafeCache[string, string](time.Second)
	var wg sync.WaitGroup

	var hits, misses int64

	// Writer goroutines: continuously put entries with short TTL
	for i := 0; i < 3; i++ {
		writerId := i
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := 0; j < 100; j++ {
				key := fmt.Sprintf("key-%d", j%10) // 10 unique keys
				value := fmt.Sprintf("writer-%d-iteration-%d", writerId, j)
				cache.Put(key, value, 100*time.Millisecond) // 100ms TTL
				time.Sleep(10 * time.Millisecond)
			}
		}()
	}

	// Reader goroutines: continuously read entries
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := 0; j < 200; j++ {
				key := fmt.Sprintf("key-%d", j%10)
				_, found := cache.Get(key)

				if found {
					atomic.AddInt64(&hits, 1)
				} else {
					atomic.AddInt64(&misses, 1)
				}

				time.Sleep(5 * time.Millisecond)
			}
		}()
	}

	wg.Wait()

	fmt.Printf("Cache hits: %d\n", hits)
	fmt.Printf("Cache misses: %d\n", misses)
	fmt.Printf("Final cache size: %d\n", cache.Size())

	// Demonstrate TTL expiration
	fmt.Println("\n--- TTL Expiration Demo ---")
	cache.Put("session", "user-123", 500*time.Millisecond) // 500ms TTL
	fmt.Println("Put 'session' with 500ms TTL")

	value, found := cache.Get("session")
	fmt.Printf("Immediate get: %s (found: %v)\n", value, found)

	time.Sleep(600 * time.Millisecond)
	value, found = cache.Get("session")
	fmt.Printf("After 600ms: %s (found: %v)\n", value, found) // Should be not found

	cache.Shutdown()
}
