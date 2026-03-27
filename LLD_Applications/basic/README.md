# basic/ - CRUD API with Middleware & Testing

Demonstrates layered architecture, REST API design, middleware chain, and real HTTP integration testing.

## Endpoints

```
POST   /users        Create user
GET    /users/:id    Get user by ID
GET    /users        List all users
PUT    /users/:id    Update user
DELETE /users/:id    Delete user
GET    /ping         Health check
```

## Example Requests

```bash
# Create
curl -X POST http://localhost:9080/users \
  -H "Content-Type: application/json" \
  -H "X-Idempotency-Key: req-12345" \
  -d '{"name":"John","email":"john@example.com"}'

# Get
curl http://localhost:9080/users/<id>

# Update
curl -X PUT http://localhost:9080/users/<id> \
  -H "Content-Type: application/json" \
  -H "X-Idempotency-Key: req-67890" \
  -d '{"name":"Jane","email":"jane@example.com"}'

# Delete
curl -X DELETE http://localhost:9080/users/<id> \
  -H "X-Idempotency-Key: req-abcdef"

# List all
curl http://localhost:9080/users
```

## Package Structure

```
basic/
├── main.go             # Entry point, singleton wiring
├── interfaces/user.go  # UserRepository + UserService interfaces
├── dto/user.go         # CreateUserRequest, UpdateUserRequest
├── model/user.go       # User entity (GORM-tagged)
├── repository/         # SQLite via GORM (Get + New constructors)
├── service/            # Business logic, UUID generation
├── controller/         # Gin HTTP handlers + RegisterRoutes
├── middleware/          # Rate limiter (token bucket), request logger
└── tests/              # Real HTTP tests via httptest.NewServer
```

## Key Patterns

- **Singleton + Constructor**: `GetUserService()` for production, `NewUserService()` for tests
- **Interface-based DI**: controller depends on `interfaces.UserService`, not concrete type
- **Token-bucket rate limiter**: `sync.Mutex`-protected custom implementation
- **Table-driven tests**: validation edge cases in `TestCreateUserValidation`
