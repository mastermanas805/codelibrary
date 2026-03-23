package main

import (
	"container/list"
	"fmt"
	"sync"
	"time"
)

type Node[K comparable, V any] struct {
	key            K
	value          V
	expirationTime time.Time
}

type LRUCache[K comparable, V any] struct {
	capacity int

	mu    sync.RWMutex
	ll    *list.List
	cache map[K]*list.Element

	stopCh chan struct{}
	wg     sync.WaitGroup
}

func NewLRUCache[K comparable, V any](capacity int, cleanupInterval time.Duration) *LRUCache[K, V] {
	c := &LRUCache[K, V]{
		capacity: capacity,
		ll:       list.New(),
		cache:    make(map[K]*list.Element),
		stopCh:   make(chan struct{}),
	}

	if cleanupInterval > 0 {
		c.wg.Add(1)
		go c.cleanupLoop(cleanupInterval)
	}

	return c
}

func (c *LRUCache[K, V]) Get(key K) (V, bool) {
	c.mu.RLock()
	ele, ok := c.cache[key]
	c.mu.RUnlock()

	if !ok {
		var zero V
		return zero, false
	}

	c.mu.Lock()
	defer c.mu.Unlock()

	// double check after upgrading lock
	ele, ok = c.cache[key]
	if !ok {
		var zero V
		return zero, false
	}

	node := ele.Value.(*Node[K, V])

	// TTL check
	if time.Now().After(node.expirationTime) {
		c.removeElement(ele)
		var zero V
		return zero, false
	}

	// move to front (LRU update)
	c.ll.MoveToFront(ele)

	return node.value, true
}

func (c *LRUCache[K, V]) Put(key K, value V, ttl time.Duration) {
	c.mu.Lock()
	defer c.mu.Unlock()

	if ele, ok := c.cache[key]; ok {
		node := ele.Value.(*Node[K, V])
		node.value = value
		node.expirationTime = time.Now().Add(ttl)
		c.ll.MoveToFront(ele)
		return
	}

	if c.ll.Len() >= c.capacity {
		c.evictLRU()
	}

	node := &Node[K, V]{
		key:            key,
		value:          value,
		expirationTime: time.Now().Add(ttl),
	}

	ele := c.ll.PushFront(node)
	c.cache[key] = ele
}

func (c *LRUCache[K, V]) evictLRU() {
	ele := c.ll.Back()
	if ele != nil {
		c.removeElement(ele)
	}
}

func (c *LRUCache[K, V]) removeElement(ele *list.Element) {
	c.ll.Remove(ele)
	node := ele.Value.(*Node[K, V])
	delete(c.cache, node.key)
}

func (c *LRUCache[K, V]) cleanupLoop(interval time.Duration) {
	defer c.wg.Done()

	ticker := time.NewTicker(interval)
	defer ticker.Stop()

	for {
		select {
		case <-c.stopCh:
			return
		case <-ticker.C:
			c.cleanupExpired()
		}
	}
}

func (c *LRUCache[K, V]) cleanupExpired() {
	c.mu.Lock()
	defer c.mu.Unlock()

	now := time.Now()

	for ele := c.ll.Back(); ele != nil; {
		prev := ele.Prev()
		node := ele.Value.(*Node[K, V])

		if now.After(node.expirationTime) {
			c.removeElement(ele)
		}

		ele = prev
	}
}

func (c *LRUCache[K, V]) Shutdown() {
	close(c.stopCh)
	c.wg.Wait()
}

func main() {
	cache := NewLRUCache[string, string](5, time.Second)

	var wg sync.WaitGroup

	// Writers
	for i := 0; i < 3; i++ {
		writerID := i
		wg.Add(1)

		go func() {
			defer wg.Done()
			for j := 0; j < 20; j++ {
				key := fmt.Sprintf("key-%d", j%5)
				value := fmt.Sprintf("writer-%d-%d", writerID, j)

				cache.Put(key, value, 500*time.Millisecond)
				time.Sleep(50 * time.Millisecond)
			}
		}()
	}

	// Readers
	for i := 0; i < 5; i++ {
		readerID := i
		wg.Add(1)

		go func() {
			defer wg.Done()
			for j := 0; j < 30; j++ {
				key := fmt.Sprintf("key-%d", j%5)

				val, ok := cache.Get(key)
				if ok {
					fmt.Printf("[Reader %d] HIT %s -> %s\n", readerID, key, val)
				} else {
					fmt.Printf("[Reader %d] MISS %s\n", readerID, key)
				}

				time.Sleep(30 * time.Millisecond)
			}
		}()
	}

	wg.Wait()

	// Final state
	fmt.Println("\n--- Final Check ---")

	for i := 0; i < 5; i++ {
		key := fmt.Sprintf("key-%d", i)
		val, ok := cache.Get(key)
		fmt.Printf("%s -> (%v, %s)\n", key, ok, val)
	}

	// TTL demo
	fmt.Println("\n--- TTL Demo ---")
	cache.Put("session", "user-123", 300*time.Millisecond)

	val, ok := cache.Get("session")
	fmt.Printf("Immediate: (%v, %s)\n", ok, val)

	time.Sleep(400 * time.Millisecond)

	val, ok = cache.Get("session")
	fmt.Printf("After expiry: (%v, %s)\n", ok, val)

	cache.Shutdown()
}
