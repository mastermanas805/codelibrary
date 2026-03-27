package tests

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
	"testing"
)

type eventResponse struct {
	ID         string `json:"id"`
	Name       string `json:"name"`
	Venue      string `json:"venue"`
	TotalSeats int    `json:"total_seats"`
}

type seatResponse struct {
	ID         string `json:"id"`
	EventID    string `json:"event_id"`
	SeatNumber int    `json:"seat_number"`
	Status     string `json:"status"`
	BookedBy   string `json:"booked_by"`
	Version    int    `json:"version"`
}

func createEvent(t *testing.T, serverURL string, totalSeats int) eventResponse {
	t.Helper()
	body := fmt.Sprintf(`{"name":"Concert","venue":"Arena","date":"2026-06-15","total_seats":%d}`, totalSeats)
	resp, err := http.Post(serverURL+"/events", "application/json", strings.NewReader(body))
	if err != nil {
		t.Fatalf("failed to create event: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusCreated {
		t.Fatalf("expected 201, got %d", resp.StatusCode)
	}

	var event eventResponse
	json.NewDecoder(resp.Body).Decode(&event)
	return event
}

func getAvailableSeats(t *testing.T, serverURL, eventID string) []seatResponse {
	t.Helper()
	resp, err := http.Get(serverURL + "/events/" + eventID + "/seats")
	if err != nil {
		t.Fatalf("failed to get seats: %v", err)
	}
	defer resp.Body.Close()

	var seats []seatResponse
	json.NewDecoder(resp.Body).Decode(&seats)
	return seats
}

func TestCreateEventAndListSeats(t *testing.T) {
	server := SetupTestServer(t)

	event := createEvent(t, server.URL, 5)
	if event.ID == "" {
		t.Fatal("expected non-empty event ID")
	}
	if event.TotalSeats != 5 {
		t.Errorf("expected 5 total seats, got %d", event.TotalSeats)
	}

	seats := getAvailableSeats(t, server.URL, event.ID)
	if len(seats) != 5 {
		t.Errorf("expected 5 available seats, got %d", len(seats))
	}

	for _, seat := range seats {
		if seat.Status != "available" {
			t.Errorf("expected status 'available', got '%s'", seat.Status)
		}
	}
}

func TestBookSeat(t *testing.T) {
	server := SetupTestServer(t)

	event := createEvent(t, server.URL, 3)
	seats := getAvailableSeats(t, server.URL, event.ID)
	if len(seats) == 0 {
		t.Fatal("no seats available")
	}

	body := fmt.Sprintf(`{"seat_id":"%s","user_id":"user-1"}`, seats[0].ID)
	resp, err := http.Post(server.URL+"/bookings", "application/json", strings.NewReader(body))
	if err != nil {
		t.Fatalf("booking failed: %v", err)
	}
	resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		t.Errorf("expected 200, got %d", resp.StatusCode)
	}

	available := getAvailableSeats(t, server.URL, event.ID)
	if len(available) != 2 {
		t.Errorf("expected 2 available seats after booking, got %d", len(available))
	}
}
