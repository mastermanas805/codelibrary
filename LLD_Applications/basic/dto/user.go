package dto

type CreateUserRequest struct {
	MutationID string `json:"mutation_id,omitempty"`
	Name       string `json:"name" binding:"required"`
	Email      string `json:"email" binding:"required,email"`
}

type UpdateUserRequest struct {
	MutationID string `json:"mutation_id,omitempty"`
	Name       string `json:"name" binding:"required"`
	Email      string `json:"email" binding:"required,email"`
}
