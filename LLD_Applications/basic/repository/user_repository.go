package repository

import (
	"errors"
	"sync"

	"gorm.io/gorm"

	"basic/model"
)

var (
	ErrUserNotFound      = errors.New("user not found")
	ErrUserAlreadyExists = errors.New("user with this email already exists")
)

type UserRepo struct {
	db *gorm.DB
}

var (
	userRepoInstance *UserRepo
	userRepoOnce     sync.Once
)

// GetUserRepository returns the singleton instance (production use).
func GetUserRepository(db *gorm.DB) *UserRepo {
	userRepoOnce.Do(func() {
		db.AutoMigrate(&model.User{})
		userRepoInstance = &UserRepo{db: db}
	})
	return userRepoInstance
}

// NewUserRepository creates a fresh instance (test use).
func NewUserRepository(db *gorm.DB) *UserRepo {
	db.AutoMigrate(&model.User{})
	return &UserRepo{db: db}
}

func (r *UserRepo) Save(user *model.User) error {
	if err := r.db.Create(user).Error; err != nil {
		if IsUniqueViolation(err) {
			return ErrUserAlreadyExists
		}
		return err
	}
	return nil
}

func (r *UserRepo) FindByID(id string) (*model.User, error) {
	var user model.User
	if err := r.db.Where("id = ?", id).First(&user).Error; err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return nil, ErrUserNotFound
		}
		return nil, err
	}
	return &user, nil
}

func (r *UserRepo) FindByEmail(email string) (*model.User, error) {
	var user model.User
	if err := r.db.Where("email = ?", email).First(&user).Error; err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return nil, ErrUserNotFound
		}
		return nil, err
	}
	return &user, nil
}

func (r *UserRepo) FindAll() ([]*model.User, error) {
	var users []*model.User
	if err := r.db.Find(&users).Error; err != nil {
		return nil, err
	}
	return users, nil
}

func (r *UserRepo) Update(user *model.User) error {
	return r.db.Save(user).Error
}

func (r *UserRepo) Delete(id string) error {
	result := r.db.Where("id = ?", id).Delete(&model.User{})
	if result.RowsAffected == 0 {
		return ErrUserNotFound
	}
	return result.Error
}
