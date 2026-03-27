package middleware

import (
	"bytes"
	"context"
	"encoding/json"
	"io"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/redis/go-redis/v9"
)

type cachedResponse struct {
	StatusCode int               `json:"status_code"`
	Headers    map[string]string `json:"headers"`
	Body       []byte            `json:"body"`
}

type bodyWriter struct {
	gin.ResponseWriter
	buf *bytes.Buffer
}

func (w *bodyWriter) Write(b []byte) (int, error) {
	w.buf.Write(b)
	return w.ResponseWriter.Write(b)
}

// extractMutationID reads the request body looking for a "mutation_id" field,
// then restores the body so downstream handlers can read it normally.
func extractMutationID(c *gin.Context) string {
	body, err := io.ReadAll(c.Request.Body)
	if err != nil {
		return ""
	}
	c.Request.Body = io.NopCloser(bytes.NewReader(body))

	var payload struct {
		MutationID string `json:"mutation_id"`
	}
	json.Unmarshal(body, &payload)
	return payload.MutationID
}

// Idempotency returns a Gin middleware that deduplicates mutating requests.
// The key is resolved in order: X-Idempotency-Key header, then mutation_id
// from the JSON body. When rdb is nil the middleware is a no-op (test mode).
func Idempotency(rdb *redis.Client, ttl time.Duration) gin.HandlerFunc {
	return func(c *gin.Context) {
		if rdb == nil {
			c.Next()
			return
		}

		if c.Request.Method == http.MethodGet ||
			c.Request.Method == http.MethodHead ||
			c.Request.Method == http.MethodOptions {
			c.Next()
			return
		}

		key := c.GetHeader("X-Idempotency-Key")
		if key == "" {
			key = extractMutationID(c)
		}
		if key == "" {
			c.Next()
			return
		}

		ctx := context.Background()
		cacheKey := "idempotency:" + key
		lockKey := "idempotency:lock:" + key

		cached, err := rdb.Get(ctx, cacheKey).Bytes()
		if err == nil {
			var resp cachedResponse
			if json.Unmarshal(cached, &resp) == nil {
				for k, v := range resp.Headers {
					c.Header(k, v)
				}
				c.Header("X-Idempotent-Replayed", "true")
				c.Data(resp.StatusCode, "application/json", resp.Body)
				c.Abort()
				return
			}
		}

		acquired, err := rdb.SetNX(ctx, lockKey, "1", 5*time.Second).Result()
		if err != nil || !acquired {
			c.AbortWithStatusJSON(http.StatusConflict, gin.H{
				"error": "duplicate request in progress",
			})
			return
		}
		defer rdb.Del(ctx, lockKey)

		bw := &bodyWriter{ResponseWriter: c.Writer, buf: &bytes.Buffer{}}
		c.Writer = bw
		c.Next()

		resp := cachedResponse{
			StatusCode: c.Writer.Status(),
			Headers:    map[string]string{"Content-Type": "application/json"},
			Body:       bw.buf.Bytes(),
		}
		if data, err := json.Marshal(resp); err == nil {
			rdb.Set(ctx, cacheKey, data, ttl)
		}
	}
}
