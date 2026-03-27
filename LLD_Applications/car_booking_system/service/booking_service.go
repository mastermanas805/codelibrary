package service

import (
	"errors"
	"fmt"
	"sync"
	"time"

	"github.com/google/uuid"

	"car_booking_system/interfaces"
	"car_booking_system/lock"
	"car_booking_system/model"
)

type BookingSvc struct {
	bookingRepo interfaces.BookingRepository
	allocator   interfaces.AllocationStrategy
	lockFactory lock.Factory
}

var (
	bookingSvcInstance *BookingSvc
	bookingSvcOnce     sync.Once
)

func GetBookingService(brepo interfaces.BookingRepository, alloc interfaces.AllocationStrategy, lf lock.Factory) *BookingSvc {
	bookingSvcOnce.Do(func() {
		bookingSvcInstance = &BookingSvc{
			bookingRepo: brepo,
			allocator:   alloc,
			lockFactory: lf,
		}
	})
	return bookingSvcInstance
}

func NewBookingService(brepo interfaces.BookingRepository, alloc interfaces.AllocationStrategy, lf lock.Factory) *BookingSvc {
	return &BookingSvc{
		bookingRepo: brepo,
		allocator:   alloc,
		lockFactory: lf,
	}
}

func (s *BookingSvc) CreateBooking(userID string, startDay, endDay int, carType string) (*model.Booking, error) {
	var lastErr error
	for attempt := 0; attempt < 10; attempt++ {
		booking, err := s.tryCreateBooking(userID, startDay, endDay, carType)
		if err == nil {
			return booking, nil
		}
		lastErr = err
		
		// If allocation failed outright (no cars available at all), we might want to return immediately
		if err.Error() == "no available cars found for the requested time window" {
			return nil, err
		}
		
		time.Sleep(50 * time.Millisecond) // brief backoff before retry
	}
	return nil, fmt.Errorf("failed to create booking after 10 attempts, last error: %w", lastErr)
}

func (s *BookingSvc) tryCreateBooking(userID string, startDay, endDay int, carType string) (*model.Booking, error) {
	// 1. Allocate car
	car, pricing, err := s.allocator.Allocate(carType, startDay, endDay)
	if err != nil {
		return nil, err
	}

	// 2. Lock the car for each requested day
	var acquiredLocks []lock.Mutex
	defer func() {
		for _, mu := range acquiredLocks {
			mu.Unlock() // Ensure unlock for all acquired locks
		}
	}()

	for day := startDay; day <= endDay; day++ {
		mu := s.lockFactory.NewMutex(fmt.Sprintf("lock:car:%s:day:%d", car.ID, day))
		if err := mu.Lock(); err != nil {
			return nil, fmt.Errorf("failed to acquire lock for day %d: %w", day, err)
		}
		acquiredLocks = append(acquiredLocks, mu)
	}

	// 3. Double check availability
	conflicts, err := s.bookingRepo.FindConflictingBookings(car.ID, startDay, endDay)
	if err != nil {
		return nil, err
	}
	if len(conflicts) > 0 {
		return nil, errors.New("car was booked concurrently")
	}

	// 4. Create booking object with CREATED state
	totalPrice := pricing.PricePerDay * float64(endDay-startDay+1)
	booking := &model.Booking{
		ID:         uuid.New().String(),
		CarID:      car.ID,
		UserID:     userID,
		StartDay:   startDay,
		EndDay:     endDay,
		TotalPrice: totalPrice,
		Status:     model.BookingStatusCreated,
		CreatedAt:  time.Now(),
		UpdatedAt:  time.Now(),
	}

	if err := s.bookingRepo.SaveBooking(booking); err != nil {
		return nil, err
	}

	// 5. Mock payment
	err = s.mockPayment()
	if err != nil {
		booking.Status = model.BookingStatusFailed
		booking.Reason = "payment failed"
		s.bookingRepo.UpdateBookingStatus(booking.ID, booking.Status, booking.Reason)
		return booking, errors.New("payment failed")
	}

	// 6. Confirm booking
	booking.Status = model.BookingStatusConfirmed
	if err := s.bookingRepo.UpdateBookingStatus(booking.ID, booking.Status, ""); err != nil {
		return nil, err
	}
	return booking, nil
}

func (s *BookingSvc) CancelBooking(userID string, bookingID string) error {
	booking, err := s.bookingRepo.FindBookingByID(bookingID)
	if err != nil {
		return err
	}
	if booking.UserID != userID {
		return errors.New("unauthorized to cancel this booking")
	}
	if booking.Status == model.BookingStatusCancelled {
		return errors.New("booking already cancelled")
	}
	
	return s.bookingRepo.UpdateBookingStatus(bookingID, model.BookingStatusCancelled, "user requested cancellation")
}

func (s *BookingSvc) mockPayment() error {
	// Assume payment succeeds
	return nil
}
