package service

import (
	"sync"
	"time"

	"github.com/google/uuid"

	"car_booking_system/interfaces"
	"car_booking_system/model"
)

type BranchSvc struct {
	repo interfaces.BranchRepository
}

var (
	branchSvcInstance *BranchSvc
	branchSvcOnce     sync.Once
)

func GetBranchService(repo interfaces.BranchRepository) *BranchSvc {
	branchSvcOnce.Do(func() {
		branchSvcInstance = &BranchSvc{repo: repo}
	})
	return branchSvcInstance
}

func NewBranchService(repo interfaces.BranchRepository) *BranchSvc {
	return &BranchSvc{repo: repo}
}

func (s *BranchSvc) AddBranch(name string) (*model.Branch, error) {
	branch := &model.Branch{
		ID:        uuid.New().String(),
		Name:      name,
		CreatedAt: time.Now(),
		UpdatedAt: time.Now(),
	}
	if err := s.repo.SaveBranch(branch); err != nil {
		return nil, err
	}
	return branch, nil
}

func (s *BranchSvc) AddCar(branchID, carType, regNo string) (*model.Car, error) {
	car := &model.Car{
		ID:        uuid.New().String(),
		BranchID:  branchID,
		Type:      carType,
		RegNo:     regNo,
		CreatedAt: time.Now(),
		UpdatedAt: time.Now(),
	}
	if err := s.repo.SaveCar(car); err != nil {
		return nil, err
	}
	return car, nil
}

func (s *BranchSvc) SetPricing(branchID, carType string, pricePerDay float64) (*model.Pricing, error) {
	// check if pricing exists, could be an update
	pricing, err := s.repo.FindPricingByBranchAndType(branchID, carType)
	if err == nil && pricing != nil {
		pricing.PricePerDay = pricePerDay
		pricing.UpdatedAt = time.Now()
		if err := s.repo.SavePricing(pricing); err != nil {
			return nil, err
		}
		return pricing, nil
	}

	newPricing := &model.Pricing{
		ID:          uuid.New().String(),
		BranchID:    branchID,
		CarType:     carType,
		PricePerDay: pricePerDay,
		CreatedAt:   time.Now(),
		UpdatedAt:   time.Now(),
	}
	if err := s.repo.SavePricing(newPricing); err != nil {
		return nil, err
	}
	return newPricing, nil
}
