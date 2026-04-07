package dto

import "uber_eats_homepage/model"

type AddRestaurantRequest struct {
	Name         string  `json:"name" binding:"required"`
	Lat          float64 `json:"lat" binding:"required"`
	Lng          float64 `json:"lng" binding:"required"`
	Cuisine      string  `json:"cuisine" binding:"required"`
	Rating       float64 `json:"rating"`
	DeliveryTime int     `json:"delivery_time"`
}

type HomepageResponse struct {
	Location          string             `json:"location_geohash"`
	NearbyRestaurants []model.Restaurant `json:"nearby_restaurants"`
	Trending          []model.Restaurant `json:"trending"`
}
