package dto

type AddBranchRequest struct {
	Name string `json:"name" binding:"required"`
}

type AddCarRequest struct {
	Type  string `json:"type" binding:"required"` // SEDAN, SUV, HATCHBACK
	RegNo string `json:"reg_no" binding:"required"`
}

type SetPricingRequest struct {
	CarType     string  `json:"car_type" binding:"required"`
	PricePerDay float64 `json:"price_per_day" binding:"required"`
}
