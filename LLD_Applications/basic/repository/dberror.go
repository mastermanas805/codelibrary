package repository

import (
	"errors"

	"github.com/jackc/pgx/v5/pgconn"
)

const (
	PgUniqueViolation     = "23505"
	PgForeignKeyViolation = "23503"
)

// IsUniqueViolation checks whether a DB error is a unique constraint violation
// using the pgconn.PgError type and SQLSTATE code 23505.
func IsUniqueViolation(err error) bool {
	var pgErr *pgconn.PgError
	if errors.As(err, &pgErr) {
		return pgErr.Code == PgUniqueViolation
	}
	return false
}
