package tests

import (
	"net/http/httptest"
	"testing"

	"github.com/gin-gonic/gin"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"

	"basic-banking/config"
	"basic-banking/controller"
	"basic-banking/lock"
	"basic-banking/middleware"
	"basic-banking/model"
	"basic-banking/repository"
	"basic-banking/service"
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

	db.Migrator().DropTable(&model.Account{})
	db.AutoMigrate(&model.Account{})

	lf := lock.NewNoOpFactory()
	repo := repository.NewAccountRepository(db)
	svc := service.NewAccountService(db, repo, lf)
	ctrl := controller.NewAccountController(svc)

	router := gin.New()
	router.Use(middleware.RequestLogger())
	router.Use(middleware.Idempotency(nil, 0))
	ctrl.RegisterRoutes(router)

	server := httptest.NewServer(router)
	t.Cleanup(func() {
		server.Close()
		db.Migrator().DropTable(&model.Account{})
	})
	return server
}
