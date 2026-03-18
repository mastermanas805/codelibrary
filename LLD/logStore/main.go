package main

import (
	"fmt"
	"sync"
	"time"
	"unsafe"
)

// Fixed: Correctly calculates the size of the elements, not the slice header
func GetElementSize[T any]() int32 {
	var zero T
	return int32(unsafe.Sizeof(zero))
}

type Deque[T any] struct {
	items    []T
	maxSize  int32
	maxBytes int32
}

func (d *Deque[T]) GetSize() int32 {
	return int32(len(d.items))
}

func (d *Deque[T]) GetTotalBytes() int32 {
	return d.GetSize() * GetElementSize[T]()
}

func (d *Deque[T]) BytesOverFlow(inputBytes int32) bool {
	return d.maxBytes < d.GetTotalBytes()+inputBytes
}

func (d *Deque[T]) SizeOverFlow(inputSize int32) bool {
	return d.maxSize < d.GetSize()+inputSize
}

func (d *Deque[T]) Evict() {
	if len(d.items) > 0 {
		d.items = d.items[1:]
	}
}

func (d *Deque[T]) PushBack(item T) {
	itemSize := GetElementSize[T]()
	if itemSize > d.maxBytes {
		return
	}

	// Evict until new item fits within constraints
	for (d.BytesOverFlow(itemSize) || d.SizeOverFlow(1)) && len(d.items) > 0 {
		d.Evict()
	}
	d.items = append(d.items, item)
}

func (d *Deque[T]) GetTopN(n int32) []T {
	size := d.GetSize()
	if n >= size {
		return d.items
	}
	return d.items[size-n:]
}

type LogStore struct {
	deque Deque[string]
	lock  sync.RWMutex
}

func (l *LogStore) Add(items []string) {
	l.lock.Lock()
	defer l.lock.Unlock()
	for _, item := range items {
		l.deque.PushBack(item)
	}
}

func (l *LogStore) Get(n int32) []string {
	l.lock.RLock()
	defer l.lock.RUnlock()
	return l.deque.GetTopN(n)
}

func main() {
	// Constraints: Max 10 items, Max 200 bytes
	store := &LogStore{
		deque: Deque[string]{
			items:    []string{},
			maxSize:  10,
			maxBytes: 200,
		},
	}

	var wg sync.WaitGroup

	// --- WRITER GOROUTINES ---
	// Start 3 different producers adding logs simultaneously
	for i := 1; i <= 3; i++ {
		wg.Add(1)
		go func(id int) {
			defer wg.Done()
			for j := 1; j <= 10; j++ {
				msg := fmt.Sprintf("Worker %d - Log %d", id, j)
				store.Add([]string{msg})
				time.Sleep(10 * time.Millisecond) // Simulate work
			}
		}(i)
	}

	// --- READER GOROUTINE ---
	// Periodically read logs while writers are active
	wg.Add(1)
	go func() {
		defer wg.Done()
		for i := 0; i < 5; i++ {
			time.Sleep(25 * time.Millisecond)
			recent := store.Get(3)
			fmt.Printf("[Reader] Latest 3 logs: %v\n", recent)
		}
	}()

	wg.Wait()
	fmt.Println("--- Final State ---")
	fmt.Printf("Total Size: %d, All Items: %v\n", store.deque.GetSize(), store.Get(10))
}
