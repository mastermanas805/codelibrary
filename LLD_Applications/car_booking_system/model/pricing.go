package model

import "time"

type Pricing struct {
	ID          string    `json:"id" gorm:"primaryKey"`
	BranchID    string    `json:"branch_id" gorm:"uniqueIndex:idx_branch_cartype"`
	CarType     string    `json:"car_type" gorm:"uniqueIndex:idx_branch_cartype"`
	PricePerDay float64   `json:"price_per_day"`
	CreatedAt   time.Time `json:"created_at"`
	UpdatedAt   time.Time `json:"updated_at"`
}
