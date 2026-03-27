package repository

import (
	"errors"
	"sync"

	"gorm.io/gorm"

	"basic-ticketmaster/model"
)

var (
	ErrSeatNotFound      = errors.New("seat not found")
	ErrSeatAlreadyBooked = errors.New("seat already booked or version conflict")
)

type SeatRepo struct {
	db *gorm.DB
}

var (
	seatRepoInstance *SeatRepo
	seatRepoOnce     sync.Once
)

func GetSeatRepository(db *gorm.DB) *SeatRepo {
	seatRepoOnce.Do(func() {
		db.AutoMigrate(&model.Seat{})
		seatRepoInstance = &SeatRepo{db: db}
	})
	return seatRepoInstance
}

func NewSeatRepository(db *gorm.DB) *SeatRepo {
	db.AutoMigrate(&model.Seat{})
	return &SeatRepo{db: db}
}

func (r *SeatRepo) Create(seat *model.Seat) error {
	return r.db.Create(seat).Error
}

func (r *SeatRepo) GetByID(id string) (*model.Seat, error) {
	var seat model.Seat
	if err := r.db.Where("id = ?", id).First(&seat).Error; err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return nil, ErrSeatNotFound
		}
		return nil, err
	}
	return &seat, nil
}

func (r *SeatRepo) GetAvailableByEvent(eventID string) ([]*model.Seat, error) {
	var seats []*model.Seat
	if err := r.db.Where("event_id = ? AND status = ?", eventID, "available").
		Order("seat_number").Find(&seats).Error; err != nil {
		return nil, err
	}
	return seats, nil
}

// BookSeat performs an optimistic lock update.
// Only succeeds if the current version matches -- prevents double-booking.
// If RowsAffected == 0, another goroutine got there first (version mismatch).
func (r *SeatRepo) BookSeat(seatID, userID string, currentVersion int) error {
	result := r.db.Model(&model.Seat{}).
		Where("id = ? AND version = ? AND status = ?", seatID, currentVersion, "available").
		Updates(map[string]interface{}{
			"status":    "booked",
			"booked_by": userID,
			"version":   currentVersion + 1,
		})
	if result.Error != nil {
		return result.Error
	}
	if result.RowsAffected == 0 {
		return ErrSeatAlreadyBooked
	}
	return nil
}
