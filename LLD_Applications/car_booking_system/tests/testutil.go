package tests

import (
	"net/http/httptest"
	"testing"

	"github.com/gin-gonic/gin"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"

	"car_booking_system/config"
	"car_booking_system/controller"
	"car_booking_system/lock"
	"car_booking_system/middleware"
	"car_booking_system/model"
	"car_booking_system/repository"
	"car_booking_system/service"
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

	db.Migrator().DropTable(&model.User{})
	db.AutoMigrate(&model.User{})

	lf := lock.NewNoOpFactory()
	repo := repository.NewUserRepository(db)
	svc := service.NewUserService(repo, lf)
	ctrl := controller.NewUserController(svc)

	router := gin.New()
	router.Use(middleware.RequestLogger())
	router.Use(middleware.Idempotency(nil, 0))
	ctrl.RegisterRoutes(router)

	server := httptest.NewServer(router)
	t.Cleanup(func() {
		server.Close()
		db.Migrator().DropTable(&model.User{})
	})
	return server
}
