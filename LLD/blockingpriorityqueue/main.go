package main

import (
	"container/heap"
	"fmt"
	"sync"
	"time"
)

// Item represents an entry in the priority queue
type Item struct {
	Value    string
	Priority int // Lower number = higher priority
}

type PriorityHeap []Item

func (h PriorityHeap) Len() int           { return len(h) }
func (h PriorityHeap) Less(i, j int) bool { return h[i].Priority < h[j].Priority }
func (h PriorityHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *PriorityHeap) Push(x interface{}) {
	*h = append(*h, x.(Item))
}

func (h *PriorityHeap) Pop() interface{} {
	old := *h
	n := len(old)
	item := old[n-1]
	*h = old[0 : n-1]
	return item
}

type PriorityBlockingQueue struct {
	lock     sync.Mutex
	notEmpty *sync.Cond
	h        *PriorityHeap
}

func NewPriorityBlockingQueue() *PriorityBlockingQueue {
	pbq := &PriorityBlockingQueue{
		h: &PriorityHeap{},
	}
	pbq.notEmpty = sync.NewCond(&pbq.lock)
	heap.Init(pbq.h)
	return pbq
}

func (pbq *PriorityBlockingQueue) Put(val string, priority int) {
	pbq.lock.Lock()
	defer pbq.lock.Unlock()

	heap.Push(pbq.h, Item{Value: val, Priority: priority})
	pbq.notEmpty.Signal() // Wake up one sleeper
}

func (pbq *PriorityBlockingQueue) Take() Item {
	pbq.lock.Lock()
	defer pbq.lock.Unlock()

	// Block if the heap is empty
	for pbq.h.Len() == 0 {
		pbq.notEmpty.Wait()
	}

	return heap.Pop(pbq.h).(Item)
}

func main() {
	queue := NewPriorityBlockingQueue()
	var wg sync.WaitGroup
	// Consumer: Starts immediately but will block until data arrives
	wg.Add(1)
	go func() {
		defer wg.Done()
		fmt.Println("[Consumer] Waiting for tasks...")
		for i := 0; i < 5; i++ {
			task := queue.Take()
			fmt.Printf("[Consumer] Processed: %s (Priority: %d)\n", task.Value, task.Priority)
			time.Sleep(500 * time.Millisecond) // Simulate work
		}
	}()

	wg.Add(1)
	// Producer: Adds tasks out of order
	go func() {
		defer wg.Done()
		tasks := []Item{
			{Value: "Low Priority Task", Priority: 10},
			{Value: "Critical Fix", Priority: 1},
			{Value: "Medium Task", Priority: 5},
			{Value: "Another Critical Fix", Priority: 2},
			{Value: "Background Job", Priority: 20},
		}

		for _, t := range tasks {
			fmt.Printf("[Producer] Adding: %s\n", t.Value)
			queue.Put(t.Value, t.Priority)
			time.Sleep(100 * time.Millisecond)
		}
	}()

	// Keep main alive long enough to see the output
	wg.Wait()
	fmt.Println("Done.")
}
