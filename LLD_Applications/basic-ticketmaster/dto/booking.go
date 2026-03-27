package dto

type BookSeatRequest struct {
	MutationID string `json:"mutation_id,omitempty"`
	SeatID     string `json:"seat_id" binding:"required"`
	UserID     string `json:"user_id" binding:"required"`
}
