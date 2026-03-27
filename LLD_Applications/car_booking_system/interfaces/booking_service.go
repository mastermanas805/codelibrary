package interfaces

import "car_booking_system/model"

type BookingService interface {
	CreateBooking(userID string, startDay, endDay int, carType string) (*model.Booking, error)
	CancelBooking(userID string, bookingID string) error
}
