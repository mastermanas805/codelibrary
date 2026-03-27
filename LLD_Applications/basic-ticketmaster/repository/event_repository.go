package repository

import (
	"errors"
	"sync"

	"gorm.io/gorm"

	"basic-ticketmaster/model"
)

var ErrEventNotFound = errors.New("event not found")

type EventRepo struct {
	db *gorm.DB
}

var (
	eventRepoInstance *EventRepo
	eventRepoOnce     sync.Once
)

func GetEventRepository(db *gorm.DB) *EventRepo {
	eventRepoOnce.Do(func() {
		db.AutoMigrate(&model.Event{})
		eventRepoInstance = &EventRepo{db: db}
	})
	return eventRepoInstance
}

func NewEventRepository(db *gorm.DB) *EventRepo {
	db.AutoMigrate(&model.Event{})
	return &EventRepo{db: db}
}

func (r *EventRepo) Create(event *model.Event) error {
	return r.db.Create(event).Error
}

func (r *EventRepo) GetByID(id string) (*model.Event, error) {
	var event model.Event
	if err := r.db.Where("id = ?", id).First(&event).Error; err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return nil, ErrEventNotFound
		}
		return nil, err
	}
	return &event, nil
}

func (r *EventRepo) GetAll() ([]*model.Event, error) {
	var events []*model.Event
	if err := r.db.Find(&events).Error; err != nil {
		return nil, err
	}
	return events, nil
}
