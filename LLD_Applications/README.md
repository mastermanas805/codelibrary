# LLD Interview Boilerplate - Golang

Three self-contained Go projects for practicing Low-Level Design interviews. Each demonstrates specific patterns with production-grade code organization, backed by PostgreSQL + Redis via Docker Compose.

## Projects

| Project | Domain | Key Patterns |
|---------|--------|-------------|
| `basic/` | User CRUD | REST API, Gin routing, GORM, middleware, singleton + DI, table-driven tests |
| `basic-banking/` | Account Transfers | **Pessimistic locking** (SELECT FOR UPDATE), DB transactions, deadlock prevention, **two-layer locking** (distributed + row-level) |
| `basic-ticketmaster/` | Seat Booking | **Optimistic locking** (version field), retry with backoff, **distributed lock on seat**, worker pool, fan-out/fan-in |

## Quick Start

```bash
cd basic            # or basic-banking, basic-ticketmaster
make up             # start Postgres + Redis containers
make run            # start Go server locally (connects to containers)
make test           # run all tests (requires Postgres from make up)
make down           # tear down containers and volumes
```

## Port Allocation (no conflicts between projects)

| Project | App (local) | PostgreSQL (Docker) | Redis (Docker) |
|---------|-------------|--------------------:|---------------:|
| `basic/` | 9080 | 5440 | 6390 |
| `basic-banking/` | 9081 | 5441 | 6391 |
| `basic-ticketmaster/` | 9082 | 5442 | 6392 |

## Pattern Quick Reference

| Pattern | Where |
|---------|-------|
| Layered Architecture (controller/service/repo) | all 3 projects |
| Interface-based DI | `interfaces/` package in each project |
| Singleton + Constructor dual | `Get...()` vs `New...()` in service/repo/controller |
| DTO separation | `dto/` package in each project |
| Env-based configuration | `config/config.go` in each project |
| Token-bucket rate limiter | `middleware/ratelimiter.go` |
| Request logging middleware | `middleware/requestlogger.go` |
| **Idempotency (X-Idempotency-Key)** | `middleware/idempotency.go` -- Redis SET NX + response caching |
| **Redis distributed lock (Redlock)** | `lock/lock.go` -- `Factory`/`Mutex` interface, Redsync impl + NoOp for tests |
| **Typed DB error handling (pgconn)** | `basic/repository/dberror.go` -- `pgconn.PgError` code checks (no string matching) |
| Distributed lock on user email | `basic/service/user_service.go` |
| Two-layer locking (distributed + row) | `basic-banking/service/account_service.go` |
| Distributed lock on seat booking | `basic-ticketmaster/service/booking_service.go` |
| Real HTTP integration tests | `tests/testutil.go` + `httptest.NewServer` |
| Pessimistic row lock (FOR UPDATE) | `basic-banking/repository/account_repository.go` |
| GORM DB transactions | `basic-banking/service/account_service.go` |
| Deadlock prevention (sorted lock order) | `basic-banking/service/account_service.go` |
| Concurrent transfer stress test | `basic-banking/tests/transfer_test.go` |
| Optimistic lock (version field CAS) | `basic-ticketmaster/repository/seat_repository.go` |
| Retry with exponential backoff | `basic-ticketmaster/service/booking_service.go` |
| Generic worker pool | `basic-ticketmaster/concurrency/workerpool.go` |
| Fan-out/fan-in pipeline | `basic-ticketmaster/concurrency/fanout.go` |
| Concurrent booking race test | `basic-ticketmaster/tests/booking_test.go` |
| Docker Compose (Postgres + Redis) | `docker-compose.yml` in each project |

## Infrastructure

Each project includes:

- **`docker-compose.yml`** -- PostgreSQL 17 + Redis 7 with health checks (infra only, server runs locally)
- **`.env.example`** -- All configurable environment variables with defaults

## Extending During Interview

1. Define your struct in `model/`
2. Add interfaces in `interfaces/`
3. Add request/response types in `dto/`
4. Implement the repository in `repository/` (with `Get...` singleton + `New...` constructor)
5. Implement business logic in `service/` (inject `lock.Factory` for distributed locking)
6. Add HTTP handlers in `controller/` with `RegisterRoutes`
7. Wire everything in `main.go`
8. Add tests in `tests/` using `SetupTestServer(t)` (uses Docker Postgres + NoOpLockFactory)

## Stack

- **HTTP**: [Gin](https://github.com/gin-gonic/gin)
- **ORM**: [GORM](https://gorm.io) + PostgreSQL
- **Cache/Locks**: [Redis](https://redis.io) + [Redsync](https://github.com/go-redsync/redsync) (Redlock algorithm)
- **IDs**: `github.com/google/uuid`
- **Testing**: `net/http/httptest` (real TCP server)
- **Infra**: Docker Compose
