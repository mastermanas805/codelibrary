package main

import (
	"fmt"
	"sync"
	"time"
)

//////////////////// ENUMS ////////////////////

type SeatType int

const (
	NORMAL SeatType = iota
	PREMIUM
)

type SeatStatus int

const (
	AVAILABLE SeatStatus = iota
	LOCKED
	BOOKED
)

//////////////////// ENTITIES ////////////////////

type Seat struct {
	SeatID string
	Type   SeatType
	Price  float64
}

type Screen struct {
	ScreenID string
	Seats    []*Seat
}

type Theater struct {
	TheaterID string
	Name      string
	City      string
	Screens   []*Screen
}

//////////////////// SHOW SEAT ////////////////////

type ShowSeat struct {
	Seat   *Seat
	Status SeatStatus
	mu     sync.Mutex
}

func (ss *ShowSeat) Reserve() bool {
	ss.mu.Lock()
	defer ss.mu.Unlock()

	if ss.Status == AVAILABLE {
		ss.Status = BOOKED
		return true
	}
	return false
}

//////////////////// SHOW ////////////////////

type Movie struct {
	MovieID  string
	Title    string
	Duration int
}

type Show struct {
	ShowID    string
	Movie     *Movie
	Screen    *Screen
	StartTime int64
	ShowSeats map[string]*ShowSeat
}

func NewShow(showID string, movie *Movie, screen *Screen, startTime int64) *Show {
	showSeats := make(map[string]*ShowSeat)

	for _, s := range screen.Seats {
		showSeats[s.SeatID] = &ShowSeat{
			Seat:   s,
			Status: AVAILABLE,
		}
	}

	return &Show{
		ShowID:    showID,
		Movie:     movie,
		Screen:    screen,
		StartTime: startTime,
		ShowSeats: showSeats,
	}
}

//////////////////// BOOKING ////////////////////

type Booking struct {
	BookingID   string
	Show        *Show
	Seats       []*ShowSeat
	UserID      string
	TotalAmount float64
	IsConfirmed bool
}

func NewBooking(id string, show *Show, seats []*ShowSeat, userID string) *Booking {
	total := 0.0
	for _, s := range seats {
		total += s.Seat.Price
	}

	return &Booking{
		BookingID:   id,
		Show:        show,
		Seats:       seats,
		UserID:      userID,
		TotalAmount: total,
		IsConfirmed: false,
	}
}

//////////////////// BOOKING SERVICE (Singleton) ////////////////////

type BookingService struct{}

var instance *BookingService
var once sync.Once

func GetBookingService() *BookingService {
	once.Do(func() {
		instance = &BookingService{}
	})
	return instance
}

func (bs *BookingService) BookTickets(userID string, show *Show, seatIDs []string) *Booking {
	selectedSeats := []*ShowSeat{}

	for _, id := range seatIDs {
		showSeat, ok := show.ShowSeats[id]
		if !ok || !showSeat.Reserve() {
			fmt.Printf("Seat %s is already taken or invalid\n", id)
			return nil
		}
		selectedSeats = append(selectedSeats, showSeat)
	}

	bookingID := fmt.Sprintf("BKG-%d", time.Now().Unix())
	booking := NewBooking(bookingID, show, selectedSeats, userID)
	booking.IsConfirmed = true

	fmt.Printf("Successfully booked %d seats for %s\n", len(seatIDs), show.Movie.Title)
	return booking
}

//////////////////// MAIN ////////////////////

func main() {

	// Setup seats
	s1 := &Seat{"A1", NORMAL, 150}
	s2 := &Seat{"A2", PREMIUM, 300}

	screen := &Screen{
		ScreenID: "SCR1",
		Seats:    []*Seat{s1, s2},
	}

	// Movie + Show
	movie := &Movie{"M1", "Interstellar", 180}
	show := NewShow("SH1", movie, screen, time.Now().Unix())

	service := GetBookingService()

	// Simulate concurrency
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {
		defer wg.Done()
		service.BookTickets("Alice", show, []string{"A1"})
	}()

	go func() {
		defer wg.Done()
		service.BookTickets("Bob", show, []string{"A1", "A2"})
	}()

	wg.Wait()
}
