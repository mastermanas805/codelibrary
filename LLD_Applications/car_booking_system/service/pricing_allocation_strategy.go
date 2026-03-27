package service

import (
	"errors"
	"sort"

	"car_booking_system/interfaces"
	"car_booking_system/model"
)

type PricingAllocationStrategy struct {
	branchRepo  interfaces.BranchRepository
	bookingRepo interfaces.BookingRepository
}

func NewPricingAllocationStrategy(branchRepo interfaces.BranchRepository, bookingRepo interfaces.BookingRepository) *PricingAllocationStrategy {
	return &PricingAllocationStrategy{
		branchRepo:  branchRepo,
		bookingRepo: bookingRepo,
	}
}

func (s *PricingAllocationStrategy) Allocate(carType string, startDay, endDay int) (*model.Car, *model.Pricing, error) {
	cars, err := s.branchRepo.FindCarsByType(carType)
	if err != nil {
		return nil, nil, err
	}

	type option struct {
		car     *model.Car
		pricing *model.Pricing
	}
	var availableOptions []option

	for _, car := range cars {
		// 1. Check availability
		conflicts, err := s.bookingRepo.FindConflictingBookings(car.ID, startDay, endDay)
		if err != nil {
			return nil, nil, err
		}
		if len(conflicts) > 0 {
			continue // Car is booked in this window
		}

		// 2. Fetch pricing
		pricing, err := s.branchRepo.FindPricingByBranchAndType(car.BranchID, carType)
		if err != nil {
			continue // If no pricing found, skip option
		}

		availableOptions = append(availableOptions, option{
			car:     car,
			pricing: pricing,
		})
	}

	if len(availableOptions) == 0 {
		return nil, nil, errors.New("no available cars found for the requested time window")
	}

	// 3. Sort options by price ASC, then by Car ID ASC for deterministic tie-breaker
	sort.Slice(availableOptions, func(i, j int) bool {
		pi := availableOptions[i].pricing.PricePerDay
		pj := availableOptions[j].pricing.PricePerDay
		if pi == pj {
			return availableOptions[i].car.ID < availableOptions[j].car.ID
		}
		return pi < pj
	})

	best := availableOptions[0]
	return best.car, best.pricing, nil
}
