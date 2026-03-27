package tests

import (
	"fmt"
	"net/http"
	"strings"
	"sync"
	"testing"
)

// TestConcurrentBookingSameSeat: 10 goroutines race to book the same seat.
// Exactly 1 must succeed (200), the rest must get conflict (409).
func TestConcurrentBookingSameSeat(t *testing.T) {
	server := SetupTestServer(t)

	event := createEvent(t, server.URL, 1)
	seats := getAvailableSeats(t, server.URL, event.ID)
	if len(seats) == 0 {
		t.Fatal("no seats available")
	}
	seatID := seats[0].ID

	const goroutines = 10
	results := make(chan int, goroutines)
	var wg sync.WaitGroup

	for i := 0; i < goroutines; i++ {
		wg.Add(1)
		go func(userID string) {
			defer wg.Done()
			body := fmt.Sprintf(`{"seat_id":"%s","user_id":"%s"}`, seatID, userID)
			resp, err := http.Post(server.URL+"/bookings", "application/json", strings.NewReader(body))
			if err != nil {
				results <- 500
				return
			}
			resp.Body.Close()
			results <- resp.StatusCode
		}(fmt.Sprintf("user-%d", i))
	}

	wg.Wait()
	close(results)

	var success, conflict int
	for code := range results {
		switch code {
		case http.StatusOK:
			success++
		case http.StatusConflict:
			conflict++
		}
	}

	if success != 1 {
		t.Errorf("expected exactly 1 successful booking, got %d", success)
	}
	if conflict != goroutines-1 {
		t.Errorf("expected %d conflicts, got %d", goroutines-1, conflict)
	}

	t.Logf("Results: %d success, %d conflict", success, conflict)
}

// TestConcurrentBookingDifferentSeats: each goroutine books a unique seat.
// All should succeed (no conflicts).
func TestConcurrentBookingDifferentSeats(t *testing.T) {
	server := SetupTestServer(t)

	event := createEvent(t, server.URL, 10)
	seats := getAvailableSeats(t, server.URL, event.ID)

	var wg sync.WaitGroup
	for i, seat := range seats {
		wg.Add(1)
		go func(seatID, userID string) {
			defer wg.Done()
			body := fmt.Sprintf(`{"seat_id":"%s","user_id":"%s"}`, seatID, userID)
			resp, err := http.Post(server.URL+"/bookings", "application/json", strings.NewReader(body))
			if err != nil {
				t.Errorf("booking failed: %v", err)
				return
			}
			resp.Body.Close()
			if resp.StatusCode != http.StatusOK {
				t.Errorf("expected 200, got %d for seat %s", resp.StatusCode, seatID)
			}
		}(seat.ID, fmt.Sprintf("user-%d", i))
	}

	wg.Wait()

	available := getAvailableSeats(t, server.URL, event.ID)
	if len(available) != 0 {
		t.Errorf("expected 0 available seats after booking all, got %d", len(available))
	}
}
