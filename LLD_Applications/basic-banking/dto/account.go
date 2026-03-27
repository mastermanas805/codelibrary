package dto

type CreateAccountRequest struct {
	MutationID     string  `json:"mutation_id,omitempty"`
	UserID         string  `json:"user_id" binding:"required"`
	InitialBalance float64 `json:"initial_balance"`
}

type TransferRequest struct {
	MutationID    string  `json:"mutation_id,omitempty"`
	FromAccountID string  `json:"from_account_id" binding:"required"`
	ToAccountID   string  `json:"to_account_id" binding:"required"`
	Amount        float64 `json:"amount" binding:"required,gt=0"`
}
