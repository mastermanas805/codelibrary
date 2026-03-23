package main

import (
	"fmt"
	"sync"
)

type State int

const (
	ZeroBeforeOdd State = iota
	Odd
	ZeroBeforeEven
	Even
)

type ZeroEvenOddCondition struct {
	n     int
	state State
	mu    sync.Mutex
	cond  *sync.Cond
}

func NewZeroEvenOddCondition(n int) *ZeroEvenOddCondition {
	z := &ZeroEvenOddCondition{
		n:     n,
		state: ZeroBeforeOdd,
	}
	z.cond = sync.NewCond(&z.mu)
	return z
}

func (z *ZeroEvenOddCondition) Zero(printZero func()) {
	for i := 1; i <= z.n; i++ {
		z.mu.Lock()
		// Wait while not in a "before" state
		for z.state != ZeroBeforeOdd && z.state != ZeroBeforeEven {
			z.cond.Wait()
		}
		printZero() // Print "0"
		// Transition to Odd or Even based on which state we were in
		if z.state == ZeroBeforeOdd {
			z.state = Odd
		} else {
			z.state = Even
		}
		z.cond.Broadcast() // Wake waiting goroutines
		z.mu.Unlock()
	}
}

func (z *ZeroEvenOddCondition) Odd(printOdd func()) {
	for i := 1; i <= z.n; i += 2 {
		z.mu.Lock()
		// Wait while not odd's turn
		for z.state != Odd {
			z.cond.Wait()
		}
		printOdd()               // Print odd number
		z.state = ZeroBeforeEven // Next: zero, then even
		z.cond.Broadcast()
		z.mu.Unlock()
	}
}

func (z *ZeroEvenOddCondition) Even(printEven func()) {
	for i := 2; i <= z.n; i += 2 {
		z.mu.Lock()
		// Wait while not even's turn
		for z.state != Even {
			z.cond.Wait()
		}
		printEven()             // Print even number
		z.state = ZeroBeforeOdd // Next: zero, then odd
		z.cond.Broadcast()
		z.mu.Unlock()
	}
}

func main() {
	n := 5
	zeo := NewZeroEvenOddCondition(n)

	var wg sync.WaitGroup
	wg.Add(3)

	// Zero Goroutine
	go func() {
		defer wg.Done()
		zeo.Zero(func() {
			fmt.Print(0)
		})
	}()

	// Odd Goroutine
	go func() {
		defer wg.Done()
		// We use a local counter to match the internal loop of the Odd method
		currentOdd := 1
		zeo.Odd(func() {
			fmt.Print(currentOdd)
			currentOdd += 2
		})
	}()

	// Even Goroutine
	go func() {
		defer wg.Done()
		// We use a local counter to match the internal loop of the Even method
		currentEven := 2
		zeo.Even(func() {
			fmt.Print(currentEven)
			currentEven += 2
		})
	}()

	wg.Wait()
	fmt.Println() // Output: 0102030405
}
