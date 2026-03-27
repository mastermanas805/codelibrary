package interfaces

import "basic/model"

type UserRepository interface {
	Save(user *model.User) error
	FindByID(id string) (*model.User, error)
	FindByEmail(email string) (*model.User, error)
	FindAll() ([]*model.User, error)
	Update(user *model.User) error
	Delete(id string) error
}
