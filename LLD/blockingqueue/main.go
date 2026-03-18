package main

import (
	"fmt"
	"sync"
	"time"
)

type BlockingQueue struct {
	lock     sync.Mutex
	notFull  *sync.Cond
	notEmpty *sync.Cond
	items    []interface{}
	capacity int
}

func NewBlockingQueue(capacity int) *BlockingQueue {
	bq := &BlockingQueue{
		items:    make([]interface{}, 0, capacity),
		capacity: capacity,
	}
	bq.notFull = sync.NewCond(&bq.lock)
	bq.notEmpty = sync.NewCond(&bq.lock)
	return bq
}

// Put adds an item to the queue, blocking if full
func (bq *BlockingQueue) Put(item interface{}) {
	bq.lock.Lock()
	defer bq.lock.Unlock()

	for len(bq.items) == bq.capacity {
		bq.notFull.Wait()
	}

	bq.items = append(bq.items, item)
	bq.notEmpty.Signal() // Notify one waiting receiver
}

// Take removes an item from the queue, blocking if empty
func (bq *BlockingQueue) Take() interface{} {
	bq.lock.Lock()
	defer bq.lock.Unlock()

	for len(bq.items) == 0 {
		bq.notEmpty.Wait()
	}

	item := bq.items[0]
	bq.items = bq.items[1:]
	bq.notFull.Signal() // Notify one waiting sender
	return item
}

func main() {
	// Initialize a queue with a small capacity to see the blocking in action
	capacity := 2
	queue := NewBlockingQueue(capacity)
	var wg sync.WaitGroup

	fmt.Printf("--- Starting Blocking Queue (Capacity: %d) ---\n", capacity)

	// 1. Start a Producer
	wg.Add(1)
	go func() {
		defer wg.Done()
		for i := 1; i <= 500; i++ {
			fmt.Printf("[Producer] Trying to put: Item %d\n", i)
			queue.Put(i)
			fmt.Printf("[Producer] Successfully put: Item %d\n", i)
			// Small sleep to keep the output readable
			time.Sleep(100 * time.Millisecond)
		}
	}()

	// 2. Start a Consumer
	wg.Add(1)
	go func() {
		defer wg.Done()
		for i := 1; i <= 500; i++ {
			// The consumer sleeps longer to force the queue to fill up
			// and trigger the "Blocking" behavior of the producer.
			time.Sleep(500 * time.Millisecond)

			item := queue.Take()
			fmt.Printf("[Consumer] Took: %v\n", item)
		}
	}()

	wg.Wait()
	fmt.Println("--- Simulation Complete ---")
}
