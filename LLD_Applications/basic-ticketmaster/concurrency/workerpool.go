package concurrency

import (
	"context"
	"sync"
)

// RunWorkerPool distributes jobs across a fixed number of goroutine workers.
// Results are collected in non-deterministic order.
// Respects context cancellation -- workers exit early if ctx is done.
func RunWorkerPool[T any, R any](ctx context.Context, workers int, jobs []T, fn func(T) R) []R {
	jobCh := make(chan T, len(jobs))
	resultCh := make(chan R, len(jobs))

	var wg sync.WaitGroup
	for i := 0; i < workers; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for job := range jobCh {
				select {
				case <-ctx.Done():
					return
				default:
					resultCh <- fn(job)
				}
			}
		}()
	}

	for _, job := range jobs {
		jobCh <- job
	}
	close(jobCh)

	wg.Wait()
	close(resultCh)

	results := make([]R, 0, len(jobs))
	for r := range resultCh {
		results = append(results, r)
	}
	return results
}
