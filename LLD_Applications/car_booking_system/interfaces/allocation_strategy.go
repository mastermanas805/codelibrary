package interfaces

import "car_booking_system/model"

type AllocationStrategy interface {
	Allocate(carType string, startDay, endDay int) (*model.Car, *model.Pricing, error)
}
