package tests

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
	"testing"
)

type userResponse struct {
	ID        string `json:"id"`
	Name      string `json:"name"`
	Email     string `json:"email"`
	CreatedAt string `json:"created_at"`
	UpdatedAt string `json:"updated_at"`
}

// --- CRUD Lifecycle Tests (real HTTP to real server) ---

func TestCreateUser(t *testing.T) {
	server := SetupTestServer(t)

	body := `{"name":"John Doe","email":"john@example.com"}`
	resp, err := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusCreated {
		t.Fatalf("expected 201, got %d", resp.StatusCode)
	}

	var user userResponse
	json.NewDecoder(resp.Body).Decode(&user)

	if user.Name != "John Doe" {
		t.Errorf("expected name 'John Doe', got '%s'", user.Name)
	}
	if user.Email != "john@example.com" {
		t.Errorf("expected email 'john@example.com', got '%s'", user.Email)
	}
	if user.ID == "" {
		t.Error("expected non-empty ID")
	}
}

func TestCreateAndGetUser(t *testing.T) {
	server := SetupTestServer(t)

	body := `{"name":"Jane Doe","email":"jane@example.com"}`
	resp, _ := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
	var created userResponse
	json.NewDecoder(resp.Body).Decode(&created)
	resp.Body.Close()

	resp, err := http.Get(server.URL + "/users/" + created.ID)
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		t.Fatalf("expected 200, got %d", resp.StatusCode)
	}

	var fetched userResponse
	json.NewDecoder(resp.Body).Decode(&fetched)
	if fetched.ID != created.ID {
		t.Errorf("ID mismatch: got %s, want %s", fetched.ID, created.ID)
	}
	if fetched.Name != "Jane Doe" {
		t.Errorf("name mismatch: got %s, want Jane Doe", fetched.Name)
	}
}

func TestGetUserNotFound(t *testing.T) {
	server := SetupTestServer(t)

	resp, err := http.Get(server.URL + "/users/nonexistent-id")
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusNotFound {
		t.Errorf("expected 404, got %d", resp.StatusCode)
	}
}

func TestDuplicateEmail(t *testing.T) {
	server := SetupTestServer(t)

	body := `{"name":"User1","email":"dup@example.com"}`
	resp, _ := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
	resp.Body.Close()

	resp, err := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusConflict {
		t.Errorf("expected 409, got %d", resp.StatusCode)
	}
}

func TestListUsers(t *testing.T) {
	server := SetupTestServer(t)

	for i := 0; i < 3; i++ {
		body := fmt.Sprintf(`{"name":"User%d","email":"user%d@example.com"}`, i, i)
		resp, _ := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
		resp.Body.Close()
	}

	resp, err := http.Get(server.URL + "/users")
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		t.Fatalf("expected 200, got %d", resp.StatusCode)
	}

	var users []userResponse
	json.NewDecoder(resp.Body).Decode(&users)
	if len(users) != 3 {
		t.Errorf("expected 3 users, got %d", len(users))
	}
}

func TestUpdateUser(t *testing.T) {
	server := SetupTestServer(t)

	body := `{"name":"Original","email":"orig@example.com"}`
	resp, _ := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
	var created userResponse
	json.NewDecoder(resp.Body).Decode(&created)
	resp.Body.Close()

	updateBody := `{"name":"Updated","email":"updated@example.com"}`
	req, _ := http.NewRequest(http.MethodPut, server.URL+"/users/"+created.ID, strings.NewReader(updateBody))
	req.Header.Set("Content-Type", "application/json")
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		t.Fatalf("expected 200, got %d", resp.StatusCode)
	}

	var updated userResponse
	json.NewDecoder(resp.Body).Decode(&updated)
	if updated.Name != "Updated" {
		t.Errorf("expected name 'Updated', got '%s'", updated.Name)
	}
	if updated.Email != "updated@example.com" {
		t.Errorf("expected email 'updated@example.com', got '%s'", updated.Email)
	}
}

func TestDeleteUser(t *testing.T) {
	server := SetupTestServer(t)

	body := `{"name":"ToDelete","email":"delete@example.com"}`
	resp, _ := http.Post(server.URL+"/users", "application/json", strings.NewReader(body))
	var created userResponse
	json.NewDecoder(resp.Body).Decode(&created)
	resp.Body.Close()

	req, _ := http.NewRequest(http.MethodDelete, server.URL+"/users/"+created.ID, nil)
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		t.Fatalf("request failed: %v", err)
	}
	resp.Body.Close()

	if resp.StatusCode != http.StatusNoContent {
		t.Errorf("expected 204, got %d", resp.StatusCode)
	}

	resp, _ = http.Get(server.URL + "/users/" + created.ID)
	defer resp.Body.Close()
	if resp.StatusCode != http.StatusNotFound {
		t.Errorf("expected 404 after delete, got %d", resp.StatusCode)
	}
}

// --- Table-Driven Validation Tests ---

func TestCreateUserValidation(t *testing.T) {
	server := SetupTestServer(t)

	tests := []struct {
		name       string
		body       string
		wantStatus int
	}{
		{"missing name", `{"email":"test@example.com"}`, http.StatusBadRequest},
		{"missing email", `{"name":"Test"}`, http.StatusBadRequest},
		{"invalid email", `{"name":"Test","email":"not-an-email"}`, http.StatusBadRequest},
		{"empty body", `{}`, http.StatusBadRequest},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			resp, err := http.Post(server.URL+"/users", "application/json", strings.NewReader(tt.body))
			if err != nil {
				t.Fatalf("request failed: %v", err)
			}
			defer resp.Body.Close()
			if resp.StatusCode != tt.wantStatus {
				t.Errorf("expected %d, got %d", tt.wantStatus, resp.StatusCode)
			}
		})
	}
}
