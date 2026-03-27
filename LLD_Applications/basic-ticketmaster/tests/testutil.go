package tests

import (
	"net/http/httptest"
	"testing"

	"github.com/gin-gonic/gin"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"

	"basic-ticketmaster/config"
	"basic-ticketmaster/controller"
	"basic-ticketmaster/lock"
	"basic-ticketmaster/middleware"
	"basic-ticketmaster/model"
	"basic-ticketmaster/repository"
	"basic-ticketmaster/service"
)

// SetupTestServer spins up a real HTTP server backed by the Docker Compose
// PostgreSQL instance. Tables are dropped and recreated for test isolation.
// Requires: docker compose up (make up)
func SetupTestServer(t *testing.T) *httptest.Server {
	t.Helper()
	gin.SetMode(gin.TestMode)

	cfg := config.Load()
	db, err := gorm.Open(postgres.Open(cfg.PostgresDSN()), &gorm.Config{})
	if err != nil {
		t.Fatalf("failed to connect to test database (is docker compose up?): %v", err)
	}

	db.Migrator().DropTable(&model.Seat{}, &model.Event{})
	db.AutoMigrate(&model.Event{}, &model.Seat{})

	lf := lock.NewNoOpFactory()
	eventRepo := repository.NewEventRepository(db)
	seatRepo := repository.NewSeatRepository(db)
	eventSvc := service.NewEventService(eventRepo, seatRepo, lf)
	bookingSvc := service.NewBookingService(seatRepo, lf)
	ctrl := controller.NewBookingController(eventSvc, bookingSvc)

	router := gin.New()
	router.Use(middleware.RequestLogger())
	router.Use(middleware.Idempotency(nil, 0))
	ctrl.RegisterRoutes(router)

	server := httptest.NewServer(router)
	t.Cleanup(func() {
		server.Close()
		db.Migrator().DropTable(&model.Seat{}, &model.Event{})
	})
	return server
}
