package controller

import (
	"errors"
	"net/http"
	"sync"

	"github.com/gin-gonic/gin"

	"car_booking_system/dto"
	"car_booking_system/interfaces"
	"car_booking_system/repository"
)

type UserCtrl struct {
	service interfaces.UserService
}

var (
	userCtrlInstance *UserCtrl
	userCtrlOnce     sync.Once
)

// GetUserController returns the singleton instance (production use).
func GetUserController(service interfaces.UserService) *UserCtrl {
	userCtrlOnce.Do(func() {
		userCtrlInstance = &UserCtrl{service: service}
	})
	return userCtrlInstance
}

// NewUserController creates a fresh instance (test use).
func NewUserController(service interfaces.UserService) *UserCtrl {
	return &UserCtrl{service: service}
}

func (ctrl *UserCtrl) CreateUser(c *gin.Context) {
	var req dto.CreateUserRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	user, err := ctrl.service.CreateUser(req.Name, req.Email)
	if err != nil {
		if errors.Is(err, repository.ErrUserAlreadyExists) {
			c.JSON(http.StatusConflict, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, user)
}

func (ctrl *UserCtrl) GetUser(c *gin.Context) {
	id := c.Param("id")
	user, err := ctrl.service.GetUser(id)
	if err != nil {
		if errors.Is(err, repository.ErrUserNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, user)
}

func (ctrl *UserCtrl) GetAllUsers(c *gin.Context) {
	users, err := ctrl.service.GetAllUsers()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, users)
}

func (ctrl *UserCtrl) UpdateUser(c *gin.Context) {
	id := c.Param("id")
	var req dto.UpdateUserRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	user, err := ctrl.service.UpdateUser(id, req.Name, req.Email)
	if err != nil {
		if errors.Is(err, repository.ErrUserNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, user)
}

func (ctrl *UserCtrl) DeleteUser(c *gin.Context) {
	id := c.Param("id")
	if err := ctrl.service.DeleteUser(id); err != nil {
		if errors.Is(err, repository.ErrUserNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusNoContent, nil)
}

func (ctrl *UserCtrl) RegisterRoutes(router *gin.Engine) {
	users := router.Group("/users")
	{
		users.POST("", ctrl.CreateUser)
		users.GET("/:id", ctrl.GetUser)
		users.GET("", ctrl.GetAllUsers)
		users.PUT("/:id", ctrl.UpdateUser)
		users.DELETE("/:id", ctrl.DeleteUser)
	}
}
