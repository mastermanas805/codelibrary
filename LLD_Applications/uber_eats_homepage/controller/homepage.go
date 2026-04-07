package controller

import (
	"net/http"
	"strconv"
	
	"uber_eats_homepage/dto"
	"uber_eats_homepage/interfaces"

	"github.com/gin-gonic/gin"
)

type HomepageController struct {
	service interfaces.HomepageService
}

func NewHomepageController(service interfaces.HomepageService) *HomepageController {
	return &HomepageController{service: service}
}

// RegisterRoutes sets up the endpoints for restaurants and homepage
func (c *HomepageController) RegisterRoutes(rg *gin.RouterGroup) {
	rg.POST("/restaurants", c.AddRestaurant)
	rg.GET("/homepage", c.GetHomepage)
}

func (c *HomepageController) AddRestaurant(ctx *gin.Context) {
	var req dto.AddRestaurantRequest
	if err := ctx.ShouldBindJSON(&req); err != nil {
		ctx.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	restaurant, err := c.service.AddRestaurant(ctx.Request.Context(), req)
	if err != nil {
		ctx.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to add restaurant"})
		return
	}

	ctx.JSON(http.StatusCreated, restaurant)
}

func (c *HomepageController) GetHomepage(ctx *gin.Context) {
	latStr := ctx.DefaultQuery("lat", "")
	lngStr := ctx.DefaultQuery("lng", "")

	if latStr == "" || lngStr == "" {
		ctx.JSON(http.StatusBadRequest, gin.H{"error": "lat and lng must be provided"})
		return
	}

	lat, err1 := strconv.ParseFloat(latStr, 64)
	lng, err2 := strconv.ParseFloat(lngStr, 64)
	if err1 != nil || err2 != nil {
		ctx.JSON(http.StatusBadRequest, gin.H{"error": "invalid lat/lng format"})
		return
	}

	resp, err := c.service.GetHomepage(ctx.Request.Context(), lat, lng)
	if err != nil {
		ctx.JSON(http.StatusInternalServerError, gin.H{"error": "Failed to load homepage"})
		return
	}

	ctx.JSON(http.StatusOK, resp)
}
