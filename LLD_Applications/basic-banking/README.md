# basic-banking/ - Pessimistic Locking & DB Transactions

Demonstrates row-level database locks, atomic multi-account transfers, deadlock prevention, and concurrent correctness testing. Only the transfer API exists -- no deposit/withdraw shortcuts that bypass the locking model.

## Endpoints

```
POST   /accounts            Create account (with initial balance)
GET    /accounts/:id        Get account
GET    /accounts             List all accounts
POST   /accounts/transfer   Transfer between accounts (atomic, locked)
GET    /ping                Health check
```

## Example Requests

```bash
# Create accounts
curl -X POST http://localhost:9081/accounts \
  -H "Content-Type: application/json" \
  -d '{"user_id":"user-1","initial_balance":1000}'

curl -X POST http://localhost:9081/accounts \
  -H "Content-Type: application/json" \
  -d '{"user_id":"user-2","initial_balance":500}'

# Transfer
curl -X POST http://localhost:9081/accounts/transfer \
  -H "Content-Type: application/json" \
  -d '{"from_account_id":"a301d576-4268-494d-9fdf-176a8d313ac4","to_account_id":"a4761ca7-6202-4b3d-b827-e160505405f0","amount":100}'
```

## Key Patterns

### Pessimistic Locking (SELECT ... FOR UPDATE)

```go
func (r *AccountRepo) GetForUpdate(tx *gorm.DB, id string) (*model.Account, error) {
    var acc model.Account
    err := tx.Clauses(clause.Locking{Strength: "UPDATE"}).
        Where("id = ?", id).First(&acc).Error
    return &acc, err
}
```

### Deadlock Prevention (sorted lock ordering)

```go
firstID, secondID := fromID, toID
if strings.Compare(fromID, toID) > 0 {
    firstID, secondID = toID, fromID
}
first, _ := s.repo.GetForUpdate(tx, firstID)
second, _ := s.repo.GetForUpdate(tx, secondID)
```

### Tests

- `TestTransfer` -- basic A->B transfer, verify both balances
- `TestTransferInsufficientFunds` -- rejected, verify no money moved
- `TestTransferToSameAccount` -- rejected
- `TestTransferNonExistentAccount` -- 404
- `TestConcurrentTransfers` -- 100 goroutines (50 A->B, 50 B->A), total balance invariant holds at $2000

## Note on SQLite

SQLite serializes all writes at the DB level. The `SELECT FOR UPDATE` generates correct SQL for Postgres/MySQL where row-level locking is meaningful.
