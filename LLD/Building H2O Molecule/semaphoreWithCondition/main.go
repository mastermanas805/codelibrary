package main

import (
	"fmt"
	"sync"
)

type NaiveH2O struct {
	mu            sync.Mutex
	cond          *sync.Cond
	hydrogenCount int
	oxygenCount   int
}

func NewNaiveH2O() *NaiveH2O {
	h := &NaiveH2O{}
	h.cond = sync.NewCond(&h.mu)
	return h
}

func (h *NaiveH2O) Hydrogen(releaseHydrogen func()) {
	h.mu.Lock()
	defer h.mu.Unlock()

	h.hydrogenCount++

	// Wait until we can form a molecule
	for h.hydrogenCount < 2 || h.oxygenCount < 1 {
		h.cond.Wait()
	}

	releaseHydrogen()
	h.hydrogenCount--

	// Problem: Race condition on molecule formation!
	h.cond.Broadcast()
}

func (h *NaiveH2O) Oxygen(releaseOxygen func()) {
	h.mu.Lock()
	defer h.mu.Unlock()

	h.oxygenCount++

	for h.hydrogenCount < 2 || h.oxygenCount < 1 {
		h.cond.Wait()
	}

	releaseOxygen()
	h.oxygenCount--

	h.cond.Broadcast()
}

func main() {
	h2o := NewNaiveH2O()

	var wg sync.WaitGroup

	releaseHydrogen := func() {
		fmt.Print("H")
	}

	releaseOxygen := func() {
		fmt.Print("O")
	}

	input := "HHHO"

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
