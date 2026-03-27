package service

import (
	"errors"
	"fmt"
	"sync"
	"time"

	"basic-ticketmaster/interfaces"
	"basic-ticketmaster/lock"
	"basic-ticketmaster/model"
	"basic-ticketmaster/repository"
)

const maxRetries = 3

var ErrBookingConflict = errors.New("booking conflict: seat was taken by another user")

type BookingSvc struct {
	seatRepo    interfaces.SeatRepository
	lockFactory lock.Factory
}

var (
	bookingSvcInstance *BookingSvc
	bookingSvcOnce     sync.Once
)

func GetBookingService(seatRepo interfaces.SeatRepository, lf lock.Factory) *BookingSvc {
	bookingSvcOnce.Do(func() {
		bookingSvcInstance = &BookingSvc{seatRepo: seatRepo, lockFactory: lf}
	})
	return bookingSvcInstance
}

func NewBookingService(seatRepo interfaces.SeatRepository, lf lock.Factory) *BookingSvc {
	return &BookingSvc{seatRepo: seatRepo, lockFactory: lf}
}

// BookSeat acquires a distributed lock on the seat ID to coordinate across
// application instances, then falls back to optimistic locking (version field)
// with retry + exponential backoff for intra-instance races.
func (s *BookingSvc) BookSeat(seatID, userID string) error {
	mu := s.lockFactory.NewMutex(fmt.Sprintf("seat:book:%s", seatID))
	if err := mu.Lock(); err != nil {
		return fmt.Errorf("failed to acquire distributed lock: %w", err)
	}
	defer mu.Unlock()

	for attempt := 0; attempt < maxRetries; attempt++ {
		seat, err := s.seatRepo.GetByID(seatID)
		if err != nil {
			return err
		}
		if seat.Status == "booked" {
			return repository.ErrSeatAlreadyBooked
		}

		err = s.seatRepo.BookSeat(seatID, userID, seat.Version)
		if err == nil {
			return nil
		}
		if !errors.Is(err, repository.ErrSeatAlreadyBooked) {
			return err
		}

		time.Sleep(time.Duration(1<<uint(attempt)) * 10 * time.Millisecond)
	}
	return ErrBookingConflict
}

func (s *BookingSvc) GetAvailableSeats(eventID string) ([]*model.Seat, error) {
	return s.seatRepo.GetAvailableByEvent(eventID)
}
