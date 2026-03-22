/*
Requirements

	The digital wallet should allow users to create an account and manage their personal information.
	Users should be able to add and remove payment methods, such as credit cards or bank accounts.
	The digital wallet should support fund transfers between users and to external accounts.
	The system should handle transaction history and provide a statement of transactions.
	The digital wallet should support multiple currencies and perform currency conversions.
	The system should ensure the security of user information and transactions.
	The digital wallet should handle concurrent transactions and ensure data consistency.
	The system should be scalable to handle a large number of users and transactions.

	Entities
		- User
		- Account
		- Wallet
		- PaymentMethod (Interface)
		- Transaction
		- Currency
*/
package main

import (
	"errors"
	"fmt"
	"sync"
	"time"
)

type Currency string

const (
	USD Currency = "USD"
	INR Currency = "INR"
)

type TransactionStatus string

const (
	PROCESSING TransactionStatus = "PROCESSING"
	COMPLETED  TransactionStatus = "COMPLETED"
	FAILED     TransactionStatus = "FAILED"
)

type TransactionType string

const (
	CREDIT TransactionType = "CREDIT"
	DEBIT  TransactionType = "DEBIT"
)

type PaymentMethod interface {
	ProcessPayment(amount float32, currency Currency) (float32, error)
	GetId() int
}

type CreditCard struct {
	id int
}

func (c *CreditCard) GetId() int {
	return c.id
}

func (c *CreditCard) ProcessPayment(amount float32, currency Currency) (float32, error) {
	// simulate success
	return amount, nil
}

type User struct {
	id   int
	name string
}

type Transaction struct {
	id              int
	from            int
	to              int
	amount          float32
	status          TransactionStatus
	currency        Currency
	timestamp       int64
	transactionType TransactionType
}

func NewTransaction(id, from, to int, amount float32, currency Currency) *Transaction {
	return &Transaction{
		id:        id,
		from:      from,
		to:        to,
		amount:    amount,
		status:    PROCESSING,
		currency:  currency,
		timestamp: time.Now().Unix(),
	}
}

func (w *WalletService) createDebitTransaction(
	senderID, receiverID int,
	amount float32,
	currency Currency,
) *Transaction {

	return &Transaction{
		id:              w.getNextTxnID(),
		from:            senderID,
		to:              receiverID,
		amount:          amount,
		currency:        currency,
		status:          PROCESSING,
		transactionType: DEBIT,
		timestamp:       time.Now().Unix(),
	}
}

func (w *WalletService) createCreditTransaction(
	senderID, receiverID int,
	amount float32,
	currency Currency,
) *Transaction {

	return &Transaction{
		id:              w.getNextTxnID(),
		from:            senderID,
		to:              receiverID,
		amount:          amount,
		currency:        currency,
		status:          PROCESSING,
		transactionType: CREDIT,
		timestamp:       time.Now().Unix(),
	}
}

type Account struct {
	id             int
	user           *User
	balance        float32
	currency       Currency
	transactions   map[int]*Transaction
	paymentMethods map[int]PaymentMethod
	lock           sync.Mutex
}

func NewAccount(id int, user *User, currency Currency) *Account {
	return &Account{
		id:             id,
		user:           user,
		balance:        0,
		currency:       currency,
		transactions:   make(map[int]*Transaction),
		paymentMethods: make(map[int]PaymentMethod),
	}
}

func (a *Account) AddPaymentMethod(pm PaymentMethod) {
	a.paymentMethods[pm.GetId()] = pm
}

func (a *Account) AddTransaction(txn *Transaction) {
	a.transactions[txn.id] = txn
}

func (a *Account) AddBalance(methodID int, amount float32) error {
	pm, exists := a.paymentMethods[methodID]
	if !exists {
		return errors.New("payment method not found")
	}

	finalAmount, err := pm.ProcessPayment(amount, a.currency)
	if err != nil {
		return err
	}

	a.lock.Lock()
	defer a.lock.Unlock()

	a.balance += finalAmount
	return nil
}

type CurrencyConversion struct {
	from  Currency
	to    Currency
	value float32
}

type WalletService struct {
	accounts       map[int]*Account
	currencyMapper map[string]float32
	txnIDCounter   int
	lock           sync.Mutex
}

func NewWalletService() *WalletService {
	return &WalletService{
		accounts:       make(map[int]*Account),
		currencyMapper: make(map[string]float32),
	}
}

func (w *WalletService) AddAccount(acc *Account) {
	w.accounts[acc.id] = acc
}

func (w *WalletService) getKey(from, to Currency) string {
	return string(from) + "-" + string(to)
}

func (w *WalletService) AddConversion(from, to Currency, rate float32) {
	w.currencyMapper[w.getKey(from, to)] = rate
}

func (w *WalletService) Convert(amount float32, from, to Currency) (float32, error) {
	if from == to {
		return amount, nil
	}

	if rate, ok := w.currencyMapper[w.getKey(from, to)]; ok {
		return amount * rate, nil
	}

	if rate, ok := w.currencyMapper[w.getKey(to, from)]; ok {
		return amount / rate, nil
	}

	return 0, errors.New("conversion not available")
}

func (w *WalletService) getNextTxnID() int {
	w.lock.Lock()
	defer w.lock.Unlock()
	w.txnIDCounter++
	return w.txnIDCounter
}

func (w *WalletService) SendMoney(senderID, receiverID int, amount float32) (err error) {
	sender, ok := w.accounts[senderID]
	if !ok {
		return errors.New("sender not found")
	}

	receiver, ok := w.accounts[receiverID]
	if !ok {
		return errors.New("receiver not found")
	}

	// deadlock-safe locking
	if senderID < receiverID {
		sender.lock.Lock()
		receiver.lock.Lock()
	} else {
		receiver.lock.Lock()
		sender.lock.Lock()
	}

	defer sender.lock.Unlock()
	defer receiver.lock.Unlock()

	if sender.balance < amount {
		return errors.New("insufficient balance")
	}

	convertedAmount, err := w.Convert(amount, sender.currency, receiver.currency)
	if err != nil {
		return err
	}

	// create transactions via helper methods
	debitTxn := w.createDebitTransaction(senderID, receiverID, amount, sender.currency)
	creditTxn := w.createCreditTransaction(senderID, receiverID, convertedAmount, receiver.currency)

	// snapshot for rollback
	originalSenderBalance := sender.balance
	originalReceiverBalance := receiver.balance

	// rollback handler
	defer func() {
		if err != nil {
			sender.balance = originalSenderBalance
			receiver.balance = originalReceiverBalance

			debitTxn.status = FAILED
			creditTxn.status = FAILED

			sender.AddTransaction(debitTxn)
			receiver.AddTransaction(creditTxn)
		}
	}()

	// apply changes
	sender.balance -= amount
	receiver.balance += convertedAmount

	// success
	debitTxn.status = COMPLETED
	creditTxn.status = COMPLETED

	sender.AddTransaction(debitTxn)
	receiver.AddTransaction(creditTxn)

	return nil
}

func main() {
	wallet := NewWalletService()

	user1 := &User{id: 1, name: "Alice"}
	user2 := &User{id: 2, name: "Bob"}

	acc1 := NewAccount(1, user1, USD)
	acc2 := NewAccount(2, user2, INR)

	cc := &CreditCard{id: 101}
	acc1.AddPaymentMethod(cc)

	wallet.AddAccount(acc1)
	wallet.AddAccount(acc2)

	wallet.AddConversion(USD, INR, 80)

	_ = acc1.AddBalance(101, 100)

	err := wallet.SendMoney(1, 2, 50)
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("Transfer Successful")
		fmt.Println("Alice Balance:", acc1.balance)
		fmt.Println("Bob Balance:", acc2.balance)
	}
}
