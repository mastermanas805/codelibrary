package controller

import (
	"errors"
	"net/http"
	"sync"
	"time"

	"github.com/gin-gonic/gin"

	"basic-ticketmaster/dto"
	"basic-ticketmaster/interfaces"
	"basic-ticketmaster/repository"
	"basic-ticketmaster/service"
)

type BookingCtrl struct {
	eventService   interfaces.EventService
	bookingService interfaces.BookingService
}

var (
	bookingCtrlInstance *BookingCtrl
	bookingCtrlOnce     sync.Once
)

func GetBookingController(eventSvc interfaces.EventService, bookingSvc interfaces.BookingService) *BookingCtrl {
	bookingCtrlOnce.Do(func() {
		bookingCtrlInstance = &BookingCtrl{eventService: eventSvc, bookingService: bookingSvc}
	})
	return bookingCtrlInstance
}

func NewBookingController(eventSvc interfaces.EventService, bookingSvc interfaces.BookingService) *BookingCtrl {
	return &BookingCtrl{eventService: eventSvc, bookingService: bookingSvc}
}

func (ctrl *BookingCtrl) CreateEvent(c *gin.Context) {
	var req dto.CreateEventRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	date, err := time.Parse("2006-01-02", req.Date)
	if err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": "invalid date format, use YYYY-MM-DD"})
		return
	}

	event, err := ctrl.eventService.CreateEvent(req.Name, req.Venue, date, req.TotalSeats)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusCreated, event)
}

func (ctrl *BookingCtrl) GetEvent(c *gin.Context) {
	id := c.Param("id")
	event, err := ctrl.eventService.GetEvent(id)
	if err != nil {
		if errors.Is(err, repository.ErrEventNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, event)
}

func (ctrl *BookingCtrl) GetAllEvents(c *gin.Context) {
	events, err := ctrl.eventService.GetAllEvents()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, events)
}

func (ctrl *BookingCtrl) GetAvailableSeats(c *gin.Context) {
	eventID := c.Param("id")
	seats, err := ctrl.bookingService.GetAvailableSeats(eventID)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, seats)
}

func (ctrl *BookingCtrl) BookSeat(c *gin.Context) {
	var req dto.BookSeatRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	err := ctrl.bookingService.BookSeat(req.SeatID, req.UserID)
	if err != nil {
		if errors.Is(err, repository.ErrSeatAlreadyBooked) || errors.Is(err, service.ErrBookingConflict) {
			c.JSON(http.StatusConflict, gin.H{"error": err.Error()})
			return
		}
		if errors.Is(err, repository.ErrSeatNotFound) {
			c.JSON(http.StatusNotFound, gin.H{"error": err.Error()})
			return
		}
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}
	c.JSON(http.StatusOK, gin.H{"message": "seat booked successfully"})
}

func (ctrl *BookingCtrl) RegisterRoutes(router *gin.Engine) {
	events := router.Group("/events")
	{
		events.POST("", ctrl.CreateEvent)
		events.GET("", ctrl.GetAllEvents)
		events.GET("/:id", ctrl.GetEvent)
		events.GET("/:id/seats", ctrl.GetAvailableSeats)
	}
	router.POST("/bookings", ctrl.BookSeat)
}
