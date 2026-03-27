package model

import "time"

type Seat struct {
	ID         string    `json:"id" gorm:"primaryKey"`
	EventID    string    `json:"event_id" gorm:"index"`
	SeatNumber int       `json:"seat_number"`
	Status     string    `json:"status" gorm:"default:available"`
	BookedBy   string    `json:"booked_by"`
	Version    int       `json:"version" gorm:"default:0"`
	CreatedAt  time.Time `json:"created_at"`
	UpdatedAt  time.Time `json:"updated_at"`
}
