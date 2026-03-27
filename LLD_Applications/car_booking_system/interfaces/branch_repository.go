package interfaces

import "car_booking_system/model"

type BranchRepository interface {
	SaveBranch(branch *model.Branch) error
	FindBranchByID(id string) (*model.Branch, error)
	FindAllBranches() ([]*model.Branch, error)

	SaveCar(car *model.Car) error
	FindCarsByType(carType string) ([]*model.Car, error)

	SavePricing(pricing *model.Pricing) error
	FindPricingByBranchAndType(branchID, carType string) (*model.Pricing, error)
}
