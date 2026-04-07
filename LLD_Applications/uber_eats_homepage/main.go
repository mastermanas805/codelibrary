package main

import (
	"log"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/redis/go-redis/v9"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"

	"uber_eats_homepage/config"
	"uber_eats_homepage/controller"
	"uber_eats_homepage/middleware"
	"uber_eats_homepage/model"
	"uber_eats_homepage/repository"
	"uber_eats_homepage/service"
)

func main() {
	cfg := config.Load()

	db, err := gorm.Open(postgres.Open(cfg.PostgresDSN()), &gorm.Config{
		Logger: logger.Default.LogMode(logger.Info),
	})
	if err != nil {
		log.Fatalf("failed to connect database: %v", err)
	}

	// AutoMigrate
	err = db.AutoMigrate(&model.Restaurant{})
	if err != nil {
		log.Fatalf("failed to migrate database: %v", err)
	}

	rdb := redis.NewClient(&redis.Options{
		Addr:     cfg.RedisAddr,
		Password: cfg.RedisPassword,
	})

	// Initialize dependencies
	redisCache := repository.NewRedisGeoCache(rdb)
	
	// Simulate 4 logical shards
	numShards := 4
	restaurantRepo := repository.NewShardedRestaurantRepository(db, numShards)
	
	homepageService := service.NewHomepageService(restaurantRepo, redisCache)
	homepageController := controller.NewHomepageController(homepageService)

	router := gin.Default()
	router.Use(middleware.RequestLogger())
	router.Use(middleware.RateLimiter(500, 1000)) // higher limits for homepage read heavy
	
	// Example idempotency setup, not strictly necessary for GET homepage but good for POST
	router.Use(middleware.Idempotency(rdb, 1*time.Minute))

	router.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{"message": "pong"})
	})

	// Register homepage endpoints
	homepageController.RegisterRoutes(&router.RouterGroup)

	log.Printf("Starting server on :%s", cfg.AppPort)
	if err := router.Run(":" + cfg.AppPort); err != nil {
		log.Fatalf("Failed to run server: %v", err)
	}
}
