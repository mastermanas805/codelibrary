package service

import (
	"errors"
	"fmt"
	"strings"
	"sync"
	"time"

	"github.com/google/uuid"
	"gorm.io/gorm"

	"basic-banking/interfaces"
	"basic-banking/lock"
	"basic-banking/model"
	"basic-banking/repository"
)

type AccountSvc struct {
	db          *gorm.DB
	repo        interfaces.AccountRepository
	lockFactory lock.Factory
}

var (
	accountSvcInstance *AccountSvc
	accountSvcOnce     sync.Once
)

func GetAccountService(db *gorm.DB, repo interfaces.AccountRepository, lf lock.Factory) *AccountSvc {
	accountSvcOnce.Do(func() {
		accountSvcInstance = &AccountSvc{db: db, repo: repo, lockFactory: lf}
	})
	return accountSvcInstance
}

func NewAccountService(db *gorm.DB, repo interfaces.AccountRepository, lf lock.Factory) *AccountSvc {
	return &AccountSvc{db: db, repo: repo, lockFactory: lf}
}

// CreateAccount uses a two-layer locking strategy identical to Transfer:
//  1. Distributed lock (Redis/Redsync) keyed on the userID -- serialises
//     account creation for the same user across application instances.
//  2. DB transaction -- ensures the row is created atomically.
func (s *AccountSvc) CreateAccount(userID string, initialBalance float64) (*model.Account, error) {
	mu := s.lockFactory.NewMutex(fmt.Sprintf("account:create:%s", userID))
	if err := mu.Lock(); err != nil {
		return nil, fmt.Errorf("failed to acquire distributed lock: %w", err)
	}
	defer mu.Unlock()

	var account *model.Account
	err := s.db.Transaction(func(tx *gorm.DB) error {
		account = &model.Account{
			ID:        uuid.New().String(),
			UserID:    userID,
			Balance:   initialBalance,
			CreatedAt: time.Now(),
			UpdatedAt: time.Now(),
		}
		return tx.Create(account).Error
	})
	if err != nil {
		return nil, err
	}
	return account, nil
}

func (s *AccountSvc) GetAccount(id string) (*model.Account, error) {
	return s.repo.GetByID(id)
}

func (s *AccountSvc) GetAllAccounts() ([]*model.Account, error) {
	return s.repo.GetAll()
}

// Transfer moves funds atomically between two accounts using a two-layer
// locking strategy:
//  1. Distributed lock (Redis/Redsync) keyed on sorted account pair --
//     coordinates across multiple application instances.
//  2. Row-level pessimistic lock (SELECT FOR UPDATE) inside a DB transaction --
//     ensures atomicity at the database level.
//
// IDs are sorted before locking to prevent deadlocks when concurrent
// transfers operate on the same pair in opposite directions.
func (s *AccountSvc) Transfer(fromID, toID string, amount float64) error {
	if fromID == toID {
		return errors.New("cannot transfer to same account")
	}

	firstID, secondID := fromID, toID
	if strings.Compare(fromID, toID) > 0 {
		firstID, secondID = toID, fromID
	}

	mu := s.lockFactory.NewMutex(fmt.Sprintf("transfer:%s:%s", firstID, secondID))
	if err := mu.Lock(); err != nil {
		return fmt.Errorf("failed to acquire distributed lock: %w", err)
	}
	defer mu.Unlock()

	return s.db.Transaction(func(tx *gorm.DB) error {
		first, err := s.repo.GetForUpdate(tx, firstID)
		if err != nil {
			return err
		}
		second, err := s.repo.GetForUpdate(tx, secondID)
		if err != nil {
			return err
		}

		var sender, receiver *model.Account
		if first.ID == fromID {
			sender, receiver = first, second
		} else {
			sender, receiver = second, first
		}

		if sender.Balance < amount {
			return repository.ErrInsufficientFunds
		}

		sender.Balance -= amount
		receiver.Balance += amount

		if err := s.repo.UpdateBalance(tx, sender); err != nil {
			return err
		}
		return s.repo.UpdateBalance(tx, receiver)
	})
}
