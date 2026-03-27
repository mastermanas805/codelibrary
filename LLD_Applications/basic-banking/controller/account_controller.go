package controller

import (
	"errors"
	"net/http"
	"sync"

	"github.com/gin-gonic/gin"

	"basic-banking/dto"
	"basic-banking/interfaces"
	"basic-banking/repository"
)

type AccountCtrl struct {
	service interfaces.AccountService
}

var (
	accountCtrlInstance *AccountCtrl
	accountCtrlOnce     sync.Once
)

func GetAccountController(service interfaces.AccountService) *AccountCtrl {
	accountCtrlOnce.Do(func() {
		accountCtrlInstance = &AccountCtrl{service: service}
	})
	return accountCtrlInstance
}

func NewAccountController(service interfaces.AccountService) *AccountCtrl {
	return &AccountCtrl{service: service}
}

func (ctrl *AccountCtrl) CreateAccount(c *gin.Context) {
	var req dto.CreateAccountRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}
	account, err := ctrl.service.CreateAccount(req.UserID, req.InitialBalance)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, account)
}

func (ctrl *AccountCtrl) GetAccount(c *gin.Context) {
	id := c.Param("id")
	account, err := ctrl.service.GetAccount(id)
	if err != nil {
		if errors.Is(err, repository.ErrAccountNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, account)
}

func (ctrl *AccountCtrl) GetAllAccounts(c *gin.Context) {
	accounts, err := ctrl.service.GetAllAccounts()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, accounts)
}

func (ctrl *AccountCtrl) Transfer(c *gin.Context) {
	var req dto.TransferRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}
	if err := ctrl.service.Transfer(req.FromAccountID, req.ToAccountID, req.Amount); err != nil {
		if errors.Is(err, repository.ErrAccountNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		if errors.Is(err, repository.ErrInsufficientFunds) {
			c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"message": "transfer successful"})
}

func (ctrl *AccountCtrl) RegisterRoutes(router *gin.Engine) {
	accounts := router.Group("/accounts")
	{
		accounts.POST("", ctrl.CreateAccount)
		accounts.GET("/:id", ctrl.GetAccount)
		accounts.GET("", ctrl.GetAllAccounts)
		accounts.POST("/transfer", ctrl.Transfer)
	}
}
