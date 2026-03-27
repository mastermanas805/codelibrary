package interfaces

import (
	"time"

	"basic-ticketmaster/model"
)

type EventRepository interface {
	Create(event *model.Event) error
	GetByID(id string) (*model.Event, error)
	GetAll() ([]*model.Event, error)
}

type EventService interface {
	CreateEvent(name, venue string, date time.Time, totalSeats int) (*model.Event, error)
	GetEvent(id string) (*model.Event, error)
	GetAllEvents() ([]*model.Event, error)
}
