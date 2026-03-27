package interfaces

import "car_booking_system/model"

type BookingRepository interface {
	SaveBooking(booking *model.Booking) error
	FindBookingByID(id string) (*model.Booking, error)
	UpdateBookingStatus(id, status, reason string) error

	// FindConflictingBookings returns bookings for a car that overlap with [startDay, endDay]
	// and are either CREATED or CONFIRMED.
	FindConflictingBookings(carID string, startDay, endDay int) ([]*model.Booking, error)
}
