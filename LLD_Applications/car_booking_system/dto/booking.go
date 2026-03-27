package dto

type CreateBookingRequest struct {
	UserID   string `json:"user_id" binding:"required"`
	CarType  string `json:"car_type" binding:"required"`
	StartDay int    `json:"start_day" binding:"required"`
	EndDay   int    `json:"end_day" binding:"required"`
}

type CancelBookingRequest struct {
	UserID string `json:"user_id" binding:"required"`
}
