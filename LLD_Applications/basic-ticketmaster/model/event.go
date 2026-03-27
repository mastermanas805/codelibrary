package model

import "time"

type Event struct {
	ID         string    `json:"id" gorm:"primaryKey"`
	Name       string    `json:"name"`
	Venue      string    `json:"venue"`
	Date       time.Time `json:"date"`
	TotalSeats int       `json:"total_seats"`
	CreatedAt  time.Time `json:"created_at"`
}
