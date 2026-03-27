package concurrency

import (
	"context"
	"sync"
)

// FanOutFanIn reads from a single input channel, distributes work across N workers,
// and merges all results into a single output channel.
// The output channel is closed when all workers finish.
func FanOutFanIn[T any, R any](ctx context.Context, input <-chan T, workers int, fn func(T) R) <-chan R {
	out := make(chan R)

	var wg sync.WaitGroup
	for i := 0; i < workers; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for item := range input {
				select {
				case <-ctx.Done():
					return
				default:
					out <- fn(item)
				}
			}
		}()
	}

	go func() {
		wg.Wait()
		close(out)
	}()

	return out
}
