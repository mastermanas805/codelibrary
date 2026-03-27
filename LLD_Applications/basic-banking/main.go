package main

import (
	"log"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/redis/go-redis/v9"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"

	"basic-banking/config"
	"basic-banking/controller"
	"basic-banking/lock"
	"basic-banking/middleware"
	"basic-banking/repository"
	"basic-banking/service"
)

func main() {
	cfg := config.Load()

	db, err := gorm.Open(postgres.Open(cfg.PostgresDSN()), &gorm.Config{
		Logger: logger.Default.LogMode(logger.Info),
	})
	if err != nil {
		log.Fatalf("failed to connect database: %v", err)
	}

	rdb := redis.NewClient(&redis.Options{
		Addr:     cfg.RedisAddr,
		Password: cfg.RedisPassword,
	})
	lockFactory := lock.NewRedisFactory(rdb)

	accountRepo := repository.GetAccountRepository(db)
	accountService := service.GetAccountService(db, accountRepo, lockFactory)
	accountController := controller.GetAccountController(accountService)

	router := gin.Default()
	router.Use(middleware.RequestLogger())
	router.Use(middleware.RateLimiter(100, 200))
	router.Use(middleware.Idempotency(rdb, 24*time.Hour))

	router.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{"message": "pong"})
	})

	accountController.RegisterRoutes(router)

	log.Printf("Starting server on :%s", cfg.AppPort)
	if err := router.Run(":" + cfg.AppPort); err != nil {
		log.Fatalf("Failed to run server: %v", err)
	}
}
