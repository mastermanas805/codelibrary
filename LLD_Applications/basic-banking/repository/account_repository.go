package repository

import (
	"errors"
	"sync"

	"gorm.io/gorm"
	"gorm.io/gorm/clause"

	"basic-banking/model"
)

var (
	ErrAccountNotFound   = errors.New("account not found")
	ErrInsufficientFunds = errors.New("insufficient funds")
)

type AccountRepo struct {
	db *gorm.DB
}

var (
	accountRepoInstance *AccountRepo
	accountRepoOnce     sync.Once
)

func GetAccountRepository(db *gorm.DB) *AccountRepo {
	accountRepoOnce.Do(func() {
		db.AutoMigrate(&model.Account{})
		accountRepoInstance = &AccountRepo{db: db}
	})
	return accountRepoInstance
}

func NewAccountRepository(db *gorm.DB) *AccountRepo {
	db.AutoMigrate(&model.Account{})
	return &AccountRepo{db: db}
}

func (r *AccountRepo) Create(account *model.Account) error {
	return r.db.Create(account).Error
}

func (r *AccountRepo) GetByID(id string) (*model.Account, error) {
	var account model.Account
	if err := r.db.Where("id = ?", id).First(&account).Error; err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return nil, ErrAccountNotFound
		}
		return nil, err
	}
	return &account, nil
}

func (r *AccountRepo) GetAll() ([]*model.Account, error) {
	var accounts []*model.Account
	if err := r.db.Find(&accounts).Error; err != nil {
		return nil, err
	}
	return accounts, nil
}

// GetForUpdate acquires a row-level pessimistic lock (SELECT ... FOR UPDATE).
// Must be called within a GORM transaction (pass the tx, not the root db).
// Note: SQLite serializes writes at the DB level; this generates correct SQL for Postgres/MySQL.
func (r *AccountRepo) GetForUpdate(tx *gorm.DB, id string) (*model.Account, error) {
	var account model.Account
	err := tx.Clauses(clause.Locking{Strength: "UPDATE"}).
		Where("id = ?", id).First(&account).Error
	if err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return nil, ErrAccountNotFound
		}
		return nil, err
	}
	return &account, nil
}

func (r *AccountRepo) UpdateBalance(tx *gorm.DB, account *model.Account) error {
	return tx.Model(account).Update("balance", account.Balance).Error
}
