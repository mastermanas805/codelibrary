package repository

import (
	"sync"
	"car_booking_system/model"
	"gorm.io/gorm"
)

type BookingRepo struct {
	db *gorm.DB
}

var (
	bookingRepoInstance *BookingRepo
	bookingRepoOnce     sync.Once
)

func GetBookingRepository(db *gorm.DB) *BookingRepo {
	bookingRepoOnce.Do(func() {
		db.AutoMigrate(&model.Booking{})
		bookingRepoInstance = &BookingRepo{db: db}
	})
	return bookingRepoInstance
}

func NewBookingRepository(db *gorm.DB) *BookingRepo {
	db.AutoMigrate(&model.Booking{})
	return &BookingRepo{db: db}
}

func (r *BookingRepo) SaveBooking(booking *model.Booking) error {
	return r.db.Save(booking).Error
}

func (r *BookingRepo) FindBookingByID(id string) (*model.Booking, error) {
	var booking model.Booking
	if err := r.db.Where("id = ?", id).First(&booking).Error; err != nil {
		return nil, err
	}
	return &booking, nil
}

func (r *BookingRepo) UpdateBookingStatus(id, status, reason string) error {
	return r.db.Model(&model.Booking{}).Where("id = ?", id).Updates(map[string]interface{}{
		"status": status,
		"reason": reason,
	}).Error
}

func (r *BookingRepo) FindConflictingBookings(carID string, startDay, endDay int) ([]*model.Booking, error) {
	var bookings []*model.Booking
	// A booking overlaps if: existing_start <= proposed_end AND existing_end >= proposed_start
	err := r.db.Where("car_id = ? AND status IN ? AND start_day <= ? AND end_day >= ?",
		carID,
		[]string{model.BookingStatusCreated, model.BookingStatusConfirmed},
		endDay,
		startDay,
	).Find(&bookings).Error
	
	if err != nil {
		return nil, err
	}
	return bookings, nil
}
