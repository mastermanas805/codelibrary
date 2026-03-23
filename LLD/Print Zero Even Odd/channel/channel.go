package main

import (
	"fmt"
	"sync"
)

type ZeroEvenOddSemaphore struct {
	n             int
	zeroSemaphore chan struct{}
	oddSemaphore  chan struct{}
	evenSemaphore chan struct{}
}

func NewZeroEvenOddSemaphore(n int) *ZeroEvenOddSemaphore {
	z := &ZeroEvenOddSemaphore{
		n:             n,
		zeroSemaphore: make(chan struct{}, 1),
		oddSemaphore:  make(chan struct{}, 1),
		evenSemaphore: make(chan struct{}, 1),
	}
	z.zeroSemaphore <- struct{}{} // Zero goes first
	return z
}

// Updated signatures to take func(int)
func (z *ZeroEvenOddSemaphore) Zero(printZero func(int)) {
	for i := 1; i <= z.n; i++ {
		<-z.zeroSemaphore
		printZero(0) // Zero always prints 0
		if i%2 == 1 {
			z.oddSemaphore <- struct{}{}
		} else {
			z.evenSemaphore <- struct{}{}
		}
	}
}

func (z *ZeroEvenOddSemaphore) Odd(printOdd func(int)) {
	for i := 1; i <= z.n; i += 2 {
		<-z.oddSemaphore
		printOdd(i) // Pass the current odd number
		z.zeroSemaphore <- struct{}{}
	}
}

func (z *ZeroEvenOddSemaphore) Even(printEven func(int)) {
	for i := 2; i <= z.n; i += 2 {
		<-z.evenSemaphore
		printEven(i) // Pass the current even number
		z.zeroSemaphore <- struct{}{}
	}
}

func main() {
	n := 5
	zeo := NewZeroEvenOddSemaphore(n)
	print := func(v int) {
		fmt.Print(v)
	}

	var wg sync.WaitGroup
	wg.Add(3)

	go func() {
		defer wg.Done()
		zeo.Zero(print)
	}()

	go func() {
		defer wg.Done()
		zeo.Odd(print)
	}()

	go func() {
		defer wg.Done()
		zeo.Even(print)
	}()

	wg.Wait()
	fmt.Println() // Output: 0102030405
}
