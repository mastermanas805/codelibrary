package main

import (
	"fmt"
	"sync"
	"time"
)

type ConcurrentMap struct {
	mu   sync.RWMutex
	data map[string]interface{}
}

func (m *ConcurrentMap) Get(key string) (interface{}, bool) {
	m.mu.RLock() // Multiple readers can hold this
	defer m.mu.RUnlock()
	val, ok := m.data[key]
	return val, ok
}

func (m *ConcurrentMap) Set(key string, value interface{}) {
	m.mu.Lock() // Only one writer can hold this
	defer m.mu.Unlock()
	m.data[key] = value
}

func NewConcurrentMap() *ConcurrentMap {
	return &ConcurrentMap{
		data: make(map[string]interface{}),
	}
}

func main() {
	cMap := NewConcurrentMap()
	var wg sync.WaitGroup

	// 1. Start multiple Writers
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			key := fmt.Sprintf("key-%d", id)
			fmt.Printf("[Writer %d] Setting %s\n", id, key)
			cMap.Set(key, id*100)
		}(i)
	}

	// 2. Start multiple Readers
	// These can run in parallel thanks to RLock()
	for i := 0; i < 5; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			// Give writers a tiny head start
			time.Sleep(10 * time.Millisecond)

			key := "key-1" // All readers look at the same key
			val, ok := cMap.Get(key)
			if ok {
				fmt.Printf("[Reader %d] Found %s: %v\n", id, key, val)
			} else {
				fmt.Printf("[Reader %d] %s not found yet\n", id, key)
			}
		}(i)
	}

	wg.Wait()
	fmt.Println("All operations finished safely.")
}
