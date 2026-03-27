package model

import "time"

const (
	CarTypeSedan     = "SEDAN"
	CarTypeSUV       = "SUV"
	CarTypeHatchback = "HATCHBACK"
)

type Car struct {
	ID        string    `json:"id" gorm:"primaryKey"`
	BranchID  string    `json:"branch_id" gorm:"index"`
	Type      string    `json:"type" gorm:"index"` // SEDAN, SUV, HATCHBACK
	RegNo     string    `json:"reg_no" gorm:"unique"`
	CreatedAt time.Time `json:"created_at"`
	UpdatedAt time.Time `json:"updated_at"`
}
