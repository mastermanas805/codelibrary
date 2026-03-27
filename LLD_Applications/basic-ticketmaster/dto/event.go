package dto

type CreateEventRequest struct {
	MutationID string `json:"mutation_id,omitempty"`
	Name       string `json:"name" binding:"required"`
	Venue      string `json:"venue" binding:"required"`
	Date       string `json:"date" binding:"required"`
	TotalSeats int    `json:"total_seats" binding:"required,gt=0"`
}
