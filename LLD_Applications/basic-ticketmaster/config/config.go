package config

import "os"

type Config struct {
	AppPort       string
	DBHost        string
	DBPort        string
	DBUser        string
	DBPassword    string
	DBName        string
	DBSSLMode     string
	RedisAddr     string
	RedisPassword string
}

func Load() *Config {
	return &Config{
		AppPort:       getEnv("APP_PORT", "9082"),
		DBHost:        getEnv("DB_HOST", "localhost"),
		DBPort:        getEnv("DB_PORT", "5442"),
		DBUser:        getEnv("DB_USER", "lld"),
		DBPassword:    getEnv("DB_PASSWORD", "lld"),
		DBName:        getEnv("DB_NAME", "ticketmaster"),
		DBSSLMode:     getEnv("DB_SSLMODE", "disable"),
		RedisAddr:     getEnv("REDIS_ADDR", "localhost:6392"),
		RedisPassword: getEnv("REDIS_PASSWORD", ""),
	}
}

func (c *Config) PostgresDSN() string {
	return "host=" + c.DBHost +
		" port=" + c.DBPort +
		" user=" + c.DBUser +
		" password=" + c.DBPassword +
		" dbname=" + c.DBName +
		" sslmode=" + c.DBSSLMode
}

func getEnv(key, fallback string) string {
	if v := os.Getenv(key); v != "" {
		return v
	}
	return fallback
}
