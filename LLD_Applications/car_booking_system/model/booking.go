package model

import "time"

const (
	BookingStatusCreated   = "CREATED"
	BookingStatusConfirmed = "CONFIRMED"
	BookingStatusCancelled = "CANCELLED"
	BookingStatusFailed    = "FAILED"
)

type Booking struct {
	ID         string    `json:"id" gorm:"primaryKey"`
	CarID      string    `json:"car_id" gorm:"index"`
	UserID     string    `json:"user_id" gorm:"index"`
	StartDay   int       `json:"start_day" gorm:"index"`
	EndDay     int       `json:"end_day" gorm:"index"`
	TotalPrice float64   `json:"total_price"`
	Status     string    `json:"status"` // CREATED, CONFIRMED, CANCELLED, FAILED
	Reason     string    `json:"reason"`
	CreatedAt  time.Time `json:"created_at"`
	UpdatedAt  time.Time `json:"updated_at"`
}
