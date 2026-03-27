package tests

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
	"testing"
)

type accountResponse struct {
	ID      string  `json:"id"`
	UserID  string  `json:"user_id"`
	Balance float64 `json:"balance"`
}

func createAccount(t *testing.T, serverURL, userID string, balance float64) accountResponse {
	t.Helper()
	body := fmt.Sprintf(`{"user_id":"%s","initial_balance":%v}`, userID, balance)
	resp, err := http.Post(serverURL+"/accounts", "application/json", strings.NewReader(body))
	if err != nil {
		t.Fatalf("failed to create account: %v", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusCreated {
		t.Fatalf("expected 201, got %d", resp.StatusCode)
	}

	var acc accountResponse
	json.NewDecoder(resp.Body).Decode(&acc)
	return acc
}

func getAccount(t *testing.T, serverURL, id string) accountResponse {
	t.Helper()
	resp, err := http.Get(serverURL + "/accounts/" + id)
	if err != nil {
		t.Fatalf("failed to get account: %v", err)
	}
	defer resp.Body.Close()

	var acc accountResponse
	json.NewDecoder(resp.Body).Decode(&acc)
	return acc
}

func transfer(t *testing.T, serverURL, fromID, toID string, amount float64) *http.Response {
	t.Helper()
	body := fmt.Sprintf(`{"from_account_id":"%s","to_account_id":"%s","amount":%v}`, fromID, toID, amount)
	resp, err := http.Post(serverURL+"/accounts/transfer", "application/json", strings.NewReader(body))
	if err != nil {
		t.Fatalf("transfer request failed: %v", err)
	}
	return resp
}

func TestCreateAccount(t *testing.T) {
	server := SetupTestServer(t)
	acc := createAccount(t, server.URL, "user-1", 1000)

	if acc.Balance != 1000 {
		t.Errorf("expected balance 1000, got %v", acc.Balance)
	}
	if acc.ID == "" {
		t.Error("expected non-empty ID")
	}
}

func TestTransfer(t *testing.T) {
	server := SetupTestServer(t)
	accA := createAccount(t, server.URL, "user-1", 1000)
	accB := createAccount(t, server.URL, "user-2", 500)

	resp := transfer(t, server.URL, accA.ID, accB.ID, 300)
	resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		t.Fatalf("expected 200, got %d", resp.StatusCode)
	}

	updatedA := getAccount(t, server.URL, accA.ID)
	updatedB := getAccount(t, server.URL, accB.ID)

	if updatedA.Balance != 700 {
		t.Errorf("expected A balance 700, got %v", updatedA.Balance)
	}
	if updatedB.Balance != 800 {
		t.Errorf("expected B balance 800, got %v", updatedB.Balance)
	}
}

func TestTransferInsufficientFunds(t *testing.T) {
	server := SetupTestServer(t)
	accA := createAccount(t, server.URL, "user-1", 100)
	accB := createAccount(t, server.URL, "user-2", 0)

	resp := transfer(t, server.URL, accA.ID, accB.ID, 200)
	resp.Body.Close()

	if resp.StatusCode != http.StatusBadRequest {
		t.Errorf("expected 400, got %d", resp.StatusCode)
	}

	// Verify no money moved
	finalA := getAccount(t, server.URL, accA.ID)
	finalB := getAccount(t, server.URL, accB.ID)
	if finalA.Balance != 100 {
		t.Errorf("expected A balance unchanged at 100, got %v", finalA.Balance)
	}
	if finalB.Balance != 0 {
		t.Errorf("expected B balance unchanged at 0, got %v", finalB.Balance)
	}
}

func TestTransferToSameAccount(t *testing.T) {
	server := SetupTestServer(t)
	acc := createAccount(t, server.URL, "user-1", 1000)

	resp := transfer(t, server.URL, acc.ID, acc.ID, 100)
	resp.Body.Close()

	if resp.StatusCode != http.StatusInternalServerError {
		t.Errorf("expected 500 for self-transfer, got %d", resp.StatusCode)
	}
}

func TestTransferNonExistentAccount(t *testing.T) {
	server := SetupTestServer(t)
	acc := createAccount(t, server.URL, "user-1", 1000)

	resp := transfer(t, server.URL, acc.ID, "nonexistent-id", 100)
	resp.Body.Close()

	if resp.StatusCode != http.StatusNotFound {
		t.Errorf("expected 404, got %d", resp.StatusCode)
	}
}
