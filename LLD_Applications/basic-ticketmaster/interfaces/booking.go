package interfaces

import "basic-ticketmaster/model"

type SeatRepository interface {
	Create(seat *model.Seat) error
	GetByID(id string) (*model.Seat, error)
	GetAvailableByEvent(eventID string) ([]*model.Seat, error)
	BookSeat(seatID, userID string, currentVersion int) error
}

type BookingService interface {
	BookSeat(seatID, userID string) error
	GetAvailableSeats(eventID string) ([]*model.Seat, error)
}
