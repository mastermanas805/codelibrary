package service

import (
	"fmt"
	"sync"
	"time"

	"github.com/google/uuid"

	"basic/interfaces"
	"basic/lock"
	"basic/model"
)

type UserSvc struct {
	repo        interfaces.UserRepository
	lockFactory lock.Factory
}

var (
	userSvcInstance *UserSvc
	userSvcOnce     sync.Once
)

func GetUserService(repo interfaces.UserRepository, lf lock.Factory) *UserSvc {
	userSvcOnce.Do(func() {
		userSvcInstance = &UserSvc{repo: repo, lockFactory: lf}
	})
	return userSvcInstance
}

func NewUserService(repo interfaces.UserRepository, lf lock.Factory) *UserSvc {
	return &UserSvc{repo: repo, lockFactory: lf}
}

// CreateUser acquires a distributed lock keyed on the email to prevent
// duplicate creation across multiple application instances.
func (s *UserSvc) CreateUser(name, email string) (*model.User, error) {
	mu := s.lockFactory.NewMutex(fmt.Sprintf("user:email:%s", email))
	if err := mu.Lock(); err != nil {
		return nil, fmt.Errorf("failed to acquire lock: %w", err)
	}
	defer mu.Unlock()

	user := &model.User{
		ID:        uuid.New().String(),
		Name:      name,
		Email:     email,
		CreatedAt: time.Now(),
		UpdatedAt: time.Now(),
	}
	if err := s.repo.Save(user); err != nil {
		return nil, err
	}
	return user, nil
}

func (s *UserSvc) GetUser(id string) (*model.User, error) {
	return s.repo.FindByID(id)
}

func (s *UserSvc) GetAllUsers() ([]*model.User, error) {
	return s.repo.FindAll()
}

// UpdateUser acquires a distributed lock keyed on the user ID to prevent
// concurrent modifications across application instances.
func (s *UserSvc) UpdateUser(id, name, email string) (*model.User, error) {
	mu := s.lockFactory.NewMutex(fmt.Sprintf("user:update:%s", id))
	if err := mu.Lock(); err != nil {
		return nil, fmt.Errorf("failed to acquire lock: %w", err)
	}
	defer mu.Unlock()

	user, err := s.repo.FindByID(id)
	if err != nil {
		return nil, err
	}
	user.Name = name
	user.Email = email
	user.UpdatedAt = time.Now()
	if err := s.repo.Update(user); err != nil {
		return nil, err
	}
	return user, nil
}

// DeleteUser acquires a distributed lock keyed on the user ID to prevent
// concurrent delete/update races across application instances.
func (s *UserSvc) DeleteUser(id string) error {
	mu := s.lockFactory.NewMutex(fmt.Sprintf("user:delete:%s", id))
	if err := mu.Lock(); err != nil {
		return fmt.Errorf("failed to acquire lock: %w", err)
	}
	defer mu.Unlock()

	return s.repo.Delete(id)
}
