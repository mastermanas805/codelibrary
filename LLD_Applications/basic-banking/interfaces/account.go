package interfaces

import (
	"basic-banking/model"

	"gorm.io/gorm"
)

type AccountRepository interface {
	Create(account *model.Account) error
	GetByID(id string) (*model.Account, error)
	GetAll() ([]*model.Account, error)
	GetForUpdate(tx *gorm.DB, id string) (*model.Account, error)
	UpdateBalance(tx *gorm.DB, account *model.Account) error
}

type AccountService interface {
	CreateAccount(userID string, initialBalance float64) (*model.Account, error)
	GetAccount(id string) (*model.Account, error)
	GetAllAccounts() ([]*model.Account, error)
	Transfer(fromID, toID string, amount float64) error
}
