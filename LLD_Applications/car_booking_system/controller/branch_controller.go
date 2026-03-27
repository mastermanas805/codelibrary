package controller

import (
	"net/http"
	"sync"

	"github.com/gin-gonic/gin"

	"car_booking_system/dto"
	"car_booking_system/interfaces"
)

type BranchCtrl struct {
	service interfaces.BranchService
}

var (
	branchCtrlInstance *BranchCtrl
	branchCtrlOnce     sync.Once
)

func GetBranchController(service interfaces.BranchService) *BranchCtrl {
	branchCtrlOnce.Do(func() {
		branchCtrlInstance = &BranchCtrl{service: service}
	})
	return branchCtrlInstance
}

func (ctrl *BranchCtrl) AddBranch(c *gin.Context) {
	var req dto.AddBranchRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	branch, err := ctrl.service.AddBranch(req.Name)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, branch)
}

func (ctrl *BranchCtrl) AddCar(c *gin.Context) {
	branchID := c.Param("id")
	var req dto.AddCarRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	car, err := ctrl.service.AddCar(branchID, req.Type, req.RegNo)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, car)
}

func (ctrl *BranchCtrl) SetPricing(c *gin.Context) {
	branchID := c.Param("id")
	var req dto.SetPricingRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	pricing, err := ctrl.service.SetPricing(branchID, req.CarType, req.PricePerDay)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, pricing)
}

func (ctrl *BranchCtrl) RegisterRoutes(router *gin.Engine) {
	branches := router.Group("/branches")
	{
		branches.POST("", ctrl.AddBranch)
		branches.POST("/:id/cars", ctrl.AddCar)
		branches.POST("/:id/pricing", ctrl.SetPricing)
	}
}
