package model

import (
	"time"

	"github.com/google/uuid"
	"gorm.io/gorm"
)

type Restaurant struct {
	ID           uuid.UUID      `gorm:"type:uuid;primary_key;" json:"id"`
	Name         string         `gorm:"type:varchar(255);not null" json:"name"`
	Lat          float64        `gorm:"not null" json:"lat"`
	Lng          float64        `gorm:"not null" json:"lng"`
	Geohash      string         `gorm:"type:varchar(12);index;not null" json:"geohash"`
	Rating       float64        `gorm:"default:0" json:"rating"`
	DeliveryTime int            `gorm:"default:30" json:"delivery_time"`
	Cuisine      string         `gorm:"type:varchar(100)" json:"cuisine"`
	ShardID      int            `gorm:"not null;default:0" json:"shard_id"` // Simulating a shard placement
	CreatedAt    time.Time      `json:"created_at"`
	UpdatedAt    time.Time      `json:"updated_at"`
	DeletedAt    gorm.DeletedAt `gorm:"index" json:"-"`
}

func (r *Restaurant) BeforeCreate(tx *gorm.DB) (err error) {
	if r.ID == uuid.Nil {
		r.ID = uuid.New()
	}
	return
}
