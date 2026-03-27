package controller

import (
	"net/http"
	"sync"

	"github.com/gin-gonic/gin"

	"car_booking_system/dto"
	"car_booking_system/interfaces"
)

type BookingCtrl struct {
	service interfaces.BookingService
}

var (
	bookingCtrlInstance *BookingCtrl
	bookingCtrlOnce     sync.Once
)

func GetBookingController(service interfaces.BookingService) *BookingCtrl {
	bookingCtrlOnce.Do(func() {
		bookingCtrlInstance = &BookingCtrl{service: service}
	})
	return bookingCtrlInstance
}

func (ctrl *BookingCtrl) CreateBooking(c *gin.Context) {
	var req dto.CreateBookingRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	booking, err := ctrl.service.CreateBooking(req.UserID, req.StartDay, req.EndDay, req.CarType)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, booking)
}

func (ctrl *BookingCtrl) CancelBooking(c *gin.Context) {
	bookingID := c.Param("id")
	var req dto.CancelBookingRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := ctrl.service.CancelBooking(req.UserID, bookingID); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"message": "booking cancelled"})
}

func (ctrl *BookingCtrl) RegisterRoutes(router *gin.Engine) {
	bookings := router.Group("/bookings")
	{
		bookings.POST("", ctrl.CreateBooking)
		bookings.PUT("/:id/cancel", ctrl.CancelBooking)
	}
}
