package interfaces

import "basic/model"

type UserService interface {
	CreateUser(name, email string) (*model.User, error)
	GetUser(id string) (*model.User, error)
	GetAllUsers() ([]*model.User, error)
	UpdateUser(id, name, email string) (*model.User, error)
	DeleteUser(id string) error
}
