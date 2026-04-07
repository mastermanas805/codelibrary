package tests

import (
	"bytes"
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"testing"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/google/uuid"

	"uber_eats_homepage/controller"
	"uber_eats_homepage/dto"
	"uber_eats_homepage/model"
	"uber_eats_homepage/service"
	"context"
)

// In memory implementations for tests
type mockGeoCache struct {
	cache map[string][]string
}
func (m *mockGeoCache) AddRestaurantToGeoCache(ctx context.Context, geohashPrefix, restaurantID string) error {
	m.cache[geohashPrefix] = append(m.cache[geohashPrefix], restaurantID)
	return nil
}
func (m *mockGeoCache) GetRestaurantsByGeoPrefixes(ctx context.Context, geohashPrefixes []string) ([]string, error) {
	var res []string
	for _, p := range geohashPrefixes {
		res = append(res, m.cache[p]...)
	}
	return res, nil
}
func (m *mockGeoCache) AddTrending(ctx context.Context, geohashPrefix string, restaurantID string) error {
	return nil
}
func (m *mockGeoCache) GetTrending(ctx context.Context, geohashPrefix string) ([]string, error) {
	return nil, nil
}

type mockRestaurantRepo struct {
	db map[string]*model.Restaurant
}
func (m *mockRestaurantRepo) Create(ctx context.Context, restaurant *model.Restaurant) error {
	restaurant.ID = uuid.New()
	restaurant.CreatedAt = time.Now()
	m.db[restaurant.ID.String()] = restaurant
	return nil
}
func (m *mockRestaurantRepo) GetByGeohashPrefixes(ctx context.Context, prefixes []string) ([]model.Restaurant, error) {
	var res []model.Restaurant
	for _, r := range m.db {
		for _, p := range prefixes {
			if len(r.Geohash) >= len(p) && r.Geohash[:len(p)] == p {
				res = append(res, *r)
				break
			}
		}
	}
	return res, nil
}
func (m *mockRestaurantRepo) GetTrending(ctx context.Context, geohash string) ([]model.Restaurant, error) {
	return nil, nil
}
func (m *mockRestaurantRepo) GetByIDs(ctx context.Context, ids []string) ([]model.Restaurant, error) {
	var res []model.Restaurant
	for _, id := range ids {
		if r, ok := m.db[id]; ok {
			res = append(res, *r)
		}
	}
	return res, nil
}

func setupTestRouter() *gin.Engine {
	gin.SetMode(gin.TestMode)
	router := gin.Default()

	repo := &mockRestaurantRepo{db: make(map[string]*model.Restaurant)}
	cache := &mockGeoCache{cache: make(map[string][]string)}
	svc := service.NewHomepageService(repo, cache)
	ctrl := controller.NewHomepageController(svc)

	ctrl.RegisterRoutes(&router.RouterGroup)
	return router
}

func TestAddRestaurantAndGetHomepage(t *testing.T) {
	router := setupTestRouter()

	// 1. Add Restaurant
	reqBody := dto.AddRestaurantRequest{
		Name:    "Test Burger",
		Lat:     37.7749,
		Lng:     -122.4194, // SF Coordinates
		Cuisine: "American",
		Rating:  4.8,
	}

	bodyData, _ := json.Marshal(reqBody)
	w := httptest.NewRecorder()
	req, _ := http.NewRequest("POST", "/restaurants", bytes.NewBuffer(bodyData))
	req.Header.Set("Content-Type", "application/json")
	router.ServeHTTP(w, req)

	if w.Code != http.StatusCreated {
		t.Fatalf("Expected status 201, got %d. Body: %s", w.Code, w.Body.String())
	}

	var created model.Restaurant
	json.Unmarshal(w.Body.Bytes(), &created)
	if created.Name != "Test Burger" || created.ID == uuid.Nil {
		t.Fatalf("Restaurant not created correctly: %+v", created)
	}

	// 2. Get Homepage nearby (Should find it)
	w2 := httptest.NewRecorder()
	req2, _ := http.NewRequest("GET", "/homepage?lat=37.77&lng=-122.42", nil)
	router.ServeHTTP(w2, req2)

	if w2.Code != http.StatusOK {
		t.Fatalf("Expected status 200, got %d", w2.Code)
	}

	var hp dto.HomepageResponse
	json.Unmarshal(w2.Body.Bytes(), &hp)

	if len(hp.NearbyRestaurants) == 0 {
		t.Fatalf("Expected nearby restaurant, got 0")
	}

	if hp.NearbyRestaurants[0].Name != "Test Burger" {
		t.Fatalf("Expected Test Burger, got %s", hp.NearbyRestaurants[0].Name)
	}

	// 3. Get Homepage far away (Should not find it)
	w3 := httptest.NewRecorder()
	// New York coordinates
	req3, _ := http.NewRequest("GET", "/homepage?lat=40.7128&lng=-74.0060", nil)
	router.ServeHTTP(w3, req3)

	if w3.Code != http.StatusOK {
		t.Fatalf("Expected status 200, got %d", w3.Code)
	}

	var hp2 dto.HomepageResponse
	json.Unmarshal(w3.Body.Bytes(), &hp2)

	if len(hp2.NearbyRestaurants) != 0 {
		t.Fatalf("Expected 0 nearby restaurants, got %d", len(hp2.NearbyRestaurants))
	}
}
