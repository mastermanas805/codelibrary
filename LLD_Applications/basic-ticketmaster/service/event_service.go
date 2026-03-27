package service

import (
	"context"
	"fmt"
	"sync"
	"time"

	"github.com/google/uuid"

	"basic-ticketmaster/concurrency"
	"basic-ticketmaster/interfaces"
	"basic-ticketmaster/lock"
	"basic-ticketmaster/model"
)

type EventSvc struct {
	eventRepo   interfaces.EventRepository
	seatRepo    interfaces.SeatRepository
	lockFactory lock.Factory
}

var (
	eventSvcInstance *EventSvc
	eventSvcOnce     sync.Once
)

func GetEventService(eventRepo interfaces.EventRepository, seatRepo interfaces.SeatRepository, lf lock.Factory) *EventSvc {
	eventSvcOnce.Do(func() {
		eventSvcInstance = &EventSvc{eventRepo: eventRepo, seatRepo: seatRepo, lockFactory: lf}
	})
	return eventSvcInstance
}

func NewEventService(eventRepo interfaces.EventRepository, seatRepo interfaces.SeatRepository, lf lock.Factory) *EventSvc {
	return &EventSvc{eventRepo: eventRepo, seatRepo: seatRepo, lockFactory: lf}
}

// CreateEvent acquires a distributed lock keyed on the event name to prevent
// duplicate events, then persists the event and bulk-creates seats using a
// worker pool.
func (s *EventSvc) CreateEvent(name, venue string, date time.Time, totalSeats int) (*model.Event, error) {
	mu := s.lockFactory.NewMutex(fmt.Sprintf("event:create:%s", name))
	if err := mu.Lock(); err != nil {
		return nil, fmt.Errorf("failed to acquire distributed lock: %w", err)
	}
	defer mu.Unlock()

	event := &model.Event{
		ID:         uuid.New().String(),
		Name:       name,
		Venue:      venue,
		Date:       date,
		TotalSeats: totalSeats,
		CreatedAt:  time.Now(),
	}
	if err := s.eventRepo.Create(event); err != nil {
		return nil, err
	}

	seatNumbers := make([]int, totalSeats)
	for i := range seatNumbers {
		seatNumbers[i] = i + 1
	}

	workers := 10
	if totalSeats < workers {
		workers = totalSeats
	}

	ctx := context.Background()
	results := concurrency.RunWorkerPool(ctx, workers, seatNumbers, func(num int) error {
		seat := &model.Seat{
			ID:         uuid.New().String(),
			EventID:    event.ID,
			SeatNumber: num,
			Status:     "available",
			Version:    0,
			CreatedAt:  time.Now(),
			UpdatedAt:  time.Now(),
		}
		return s.seatRepo.Create(seat)
	})

	for _, err := range results {
		if err != nil {
			return nil, fmt.Errorf("failed to create seats: %w", err)
		}
	}

	return event, nil
}

func (s *EventSvc) GetEvent(id string) (*model.Event, error) {
	return s.eventRepo.GetByID(id)
}

func (s *EventSvc) GetAllEvents() ([]*model.Event, error) {
	return s.eventRepo.GetAll()
}
