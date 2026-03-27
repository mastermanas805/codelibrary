package repository

import (
	"sync"
	"car_booking_system/model"
	"gorm.io/gorm"
)

type BranchRepo struct {
	db *gorm.DB
}

var (
	branchRepoInstance *BranchRepo
	branchRepoOnce     sync.Once
)

func GetBranchRepository(db *gorm.DB) *BranchRepo {
	branchRepoOnce.Do(func() {
		db.AutoMigrate(&model.Branch{}, &model.Car{}, &model.Pricing{})
		branchRepoInstance = &BranchRepo{db: db}
	})
	return branchRepoInstance
}

func NewBranchRepository(db *gorm.DB) *BranchRepo {
	db.AutoMigrate(&model.Branch{}, &model.Car{}, &model.Pricing{})
	return &BranchRepo{db: db}
}

func (r *BranchRepo) SaveBranch(branch *model.Branch) error {
	return r.db.Save(branch).Error
}

func (r *BranchRepo) FindBranchByID(id string) (*model.Branch, error) {
	var branch model.Branch
	if err := r.db.Where("id = ?", id).First(&branch).Error; err != nil {
		return nil, err
	}
	return &branch, nil
}

func (r *BranchRepo) FindAllBranches() ([]*model.Branch, error) {
	var branches []*model.Branch
	if err := r.db.Find(&branches).Error; err != nil {
		return nil, err
	}
	return branches, nil
}

func (r *BranchRepo) SaveCar(car *model.Car) error {
	return r.db.Save(car).Error
}

func (r *BranchRepo) FindCarsByType(carType string) ([]*model.Car, error) {
	var cars []*model.Car
	if err := r.db.Where("type = ?", carType).Find(&cars).Error; err != nil {
		return nil, err
	}
	return cars, nil
}

func (r *BranchRepo) SavePricing(pricing *model.Pricing) error {
	return r.db.Save(pricing).Error
}

func (r *BranchRepo) FindPricingByBranchAndType(branchID, carType string) (*model.Pricing, error) {
	var pricing model.Pricing
	if err := r.db.Where("branch_id = ? AND car_type = ?", branchID, carType).First(&pricing).Error; err != nil {
		return nil, err
	}
	return &pricing, nil
}
