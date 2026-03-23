package main

import (
	"sync"
)

type FooBarCondition struct {
	n       int
	fooTurn bool
	mu      sync.Mutex
	cond    *sync.Cond
}

func NewFooBarCondition(n int) *FooBarCondition {
	fb := &FooBarCondition{
		n:       n,
		fooTurn: true,
	}
	fb.cond = sync.NewCond(&fb.mu)
	return fb
}

func (fb *FooBarCondition) Foo(printFoo func()) {
	for i := 0; i < fb.n; i++ {
		fb.mu.Lock()
		// Wait while it's not foo's turn
		for !fb.fooTurn {
			fb.cond.Wait()
		}
		printFoo()         // Print "foo"
		fb.fooTurn = false // Now bar's turn
		fb.cond.Signal()   // Wake bar
		fb.mu.Unlock()
	}
}

func (fb *FooBarCondition) Bar(printBar func()) {
	for i := 0; i < fb.n; i++ {
		fb.mu.Lock()
		// Wait while it's not bar's turn
		for fb.fooTurn {
			fb.cond.Wait()
		}
		printBar()        // Print "bar"
		fb.fooTurn = true // Now foo's turn
		fb.cond.Signal()  // Wake foo
		fb.mu.Unlock()
	}
}

func main() {
	n := 5 // Number of times to print "foobar"
	fb := NewFooBarCondition(n)

	var wg sync.WaitGroup
	wg.Add(2)

	// Goroutine for printing "foo"
	go func() {
		defer wg.Done()
		fb.Foo(func() {
			print("foo")
		})
	}()

	// Goroutine for printing "bar"
	go func() {
		defer wg.Done()
		fb.Bar(func() {
			println("bar")
		})
	}()

	wg.Wait()
}
