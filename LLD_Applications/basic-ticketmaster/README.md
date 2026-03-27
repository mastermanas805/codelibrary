# basic-ticketmaster/ - Optimistic Locking & Concurrency Patterns

Demonstrates optimistic locking via version fields, retry with backoff, generic worker pool, and fan-out/fan-in pipelines.

## Endpoints

```
POST   /events              Create event (bulk-creates seats via worker pool)
GET    /events               List all events
GET    /events/:id          Get event
GET    /events/:id/seats    List available seats
POST   /bookings            Book a seat (optimistic lock + retry)
GET    /ping                Health check
```

## Example Requests

```bash
# Create event with 100 seats
curl -X POST http://localhost:8080/events \
  -H "Content-Type: application/json" \
  -d '{"name":"Concert","venue":"Arena","date":"2026-06-15","total_seats":100}'

# List available seats
curl http://localhost:8080/events/<event-id>/seats

# Book a seat
curl -X POST http://localhost:8080/bookings \
  -H "Content-Type: application/json" \
  -d '{"seat_id":"<seat-id>","user_id":"user-1"}'
```

## Key Patterns

### Optimistic Locking (version field CAS)

```go
result := r.db.Model(&model.Seat{}).
    Where("id = ? AND version = ? AND status = ?", seatID, currentVersion, "available").
    Updates(map[string]interface{}{
        "status": "booked", "booked_by": userID, "version": currentVersion + 1,
    })
if result.RowsAffected == 0 {
    return ErrSeatAlreadyBooked // version mismatch = someone else booked it
}
```

### Retry with Exponential Backoff

```go
for attempt := 0; attempt < maxRetries; attempt++ {
    seat, _ := s.seatRepo.GetByID(seatID)
    if err := s.seatRepo.BookSeat(seatID, userID, seat.Version); err == nil {
        return nil
    }
    time.Sleep(time.Duration(1<<uint(attempt)) * 10 * time.Millisecond)
}
```

### Generic Worker Pool

```go
results := concurrency.RunWorkerPool(ctx, 10, seatNumbers, func(num int) error {
    return s.seatRepo.Create(&model.Seat{...})
})
```

### Concurrent Booking Race Test

`tests/booking_test.go`: 10 goroutines race to book the same seat via real HTTP. Exactly 1 succeeds (200), 9 get conflict (409).

## Concurrency Package

- `concurrency/workerpool.go` - Generic `RunWorkerPool[T, R]` with context cancellation
- `concurrency/fanout.go` - Generic `FanOutFanIn[T, R]` pipeline with WaitGroup-based shutdown
