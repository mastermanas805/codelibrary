package main

import (
	"fmt"
	"sync"
)

type H2O struct {
	hSem chan struct{}
	oSem chan struct{}

	mu      sync.Mutex
	count   int
	barrier *sync.Cond
}

func NewH2O() *H2O {
	h := &H2O{
		hSem: make(chan struct{}, 2),
		oSem: make(chan struct{}, 1),
	}
	h.barrier = sync.NewCond(&h.mu)

	// initial permits
	h.hSem <- struct{}{}
	h.hSem <- struct{}{}
	h.oSem <- struct{}{}

	return h
}

func (h *H2O) Hydrogen(releaseHydrogen func()) {
	<-h.hSem

	releaseHydrogen()

	h.waitBarrier()

	// refill handled only by last thread
}

func (h *H2O) Oxygen(releaseOxygen func()) {
	<-h.oSem

	releaseOxygen()

	h.waitBarrier()
}

func (h *H2O) waitBarrier() {
	h.mu.Lock()
	defer h.mu.Unlock()

	h.count++

	if h.count == 3 {
		// last thread
		h.count = 0

		// refill permits
		h.hSem <- struct{}{}
		h.hSem <- struct{}{}
		h.oSem <- struct{}{}

		h.barrier.Broadcast()
	} else {
		h.barrier.Wait()
	}
}

func main() {
	h2o := NewH2O()

	var wg sync.WaitGroup

	releaseHydrogen := func() {
		fmt.Print("H")
	}

	releaseOxygen := func() {
		fmt.Print("O")
	}

	input := "HHHOOH"

	for _, ch := range input {
		wg.Add(1)

		if ch == 'H' {
			go func() {
				defer wg.Done()
				h2o.Hydrogen(releaseHydrogen)
			}()
		} else {
			go func() {
				defer wg.Done()
				h2o.Oxygen(releaseOxygen)
			}()
		}
	}

	wg.Wait()
	fmt.Println()
}
