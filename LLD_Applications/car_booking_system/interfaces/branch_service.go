package interfaces

import "car_booking_system/model"

type BranchService interface {
	AddBranch(name string) (*model.Branch, error)
	AddCar(branchID, carType, regNo string) (*model.Car, error)
	SetPricing(branchID, carType string, pricePerDay float64) (*model.Pricing, error)
}
