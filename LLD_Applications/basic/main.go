package main

import (
	"log"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/redis/go-redis/v9"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"

	"basic/config"
	"basic/controller"
	"basic/lock"
	"basic/middleware"
	"basic/repository"
	"basic/service"
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

	userRepo := repository.GetUserRepository(db)
	userService := service.GetUserService(userRepo, lockFactory)
	userController := controller.GetUserController(userService)

	router := gin.Default()
	router.Use(middleware.RequestLogger())
	router.Use(middleware.RateLimiter(100, 200))
	router.Use(middleware.Idempotency(rdb, 1*time.Minute))

	router.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{"message": "pong"})
	})

	userController.RegisterRoutes(router)

	log.Printf("Starting server on :%s", cfg.AppPort)
	if err := router.Run(":" + cfg.AppPort); err != nil {
		log.Fatalf("Failed to run server: %v", err)
	}
}
