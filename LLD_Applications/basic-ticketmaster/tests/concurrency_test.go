package tests

import (
	"context"
	"sort"
	"testing"

	"basic-ticketmaster/concurrency"
)

func TestWorkerPool(t *testing.T) {
	jobs := make([]int, 100)
	for i := range jobs {
		jobs[i] = i + 1
	}

	ctx := context.Background()
	results := concurrency.RunWorkerPool(ctx, 5, jobs, func(n int) int {
		return n * 2
	})

	if len(results) != 100 {
		t.Fatalf("expected 100 results, got %d", len(results))
	}

	sort.Ints(results)
	for i, r := range results {
		expected := (i + 1) * 2
		if r != expected {
			t.Errorf("result[%d] = %d, expected %d", i, r, expected)
		}
	}
}

func TestFanOutFanIn(t *testing.T) {
	input := make(chan int, 20)
	for i := 1; i <= 20; i++ {
		input <- i
	}
	close(input)

	ctx := context.Background()
	output := concurrency.FanOutFanIn(ctx, input, 4, func(n int) int {
		return n * 3
	})

	var results []int
	for r := range output {
		results = append(results, r)
	}

	if len(results) != 20 {
		t.Fatalf("expected 20 results, got %d", len(results))
	}

	sort.Ints(results)
	for i, r := range results {
		expected := (i + 1) * 3
		if r != expected {
			t.Errorf("result[%d] = %d, expected %d", i, r, expected)
		}
	}
}

func TestWorkerPoolContextCancellation(t *testing.T) {
	ctx, cancel := context.WithCancel(context.Background())
	cancel()

	jobs := make([]int, 1000)
	for i := range jobs {
		jobs[i] = i
	}

	results := concurrency.RunWorkerPool(ctx, 5, jobs, func(n int) int {
		return n
	})

	// With immediate cancellation, workers may process some or no jobs
	t.Logf("processed %d/%d jobs before cancellation took effect", len(results), len(jobs))
}
