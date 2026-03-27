package tests

import (
	"fmt"
	"math"
	"net/http"
	"strings"
	"sync"
	"testing"
)

// TestConcurrentTransfers proves atomicity: 50 goroutines transfer A->B
// and 50 goroutines transfer B->A simultaneously. The total balance across
// both accounts must remain $2000 regardless of interleaving.
func TestConcurrentTransfers(t *testing.T) {
	server := SetupTestServer(t)

	accA := createAccount(t, server.URL, "user-a", 1000)
	accB := createAccount(t, server.URL, "user-b", 1000)

	const transfers = 50
	var wg sync.WaitGroup

	for i := 0; i < transfers; i++ {
		wg.Add(2)
		go func() {
			defer wg.Done()
			body := fmt.Sprintf(`{"from_account_id":"%s","to_account_id":"%s","amount":10}`, accA.ID, accB.ID)
			resp, err := http.Post(server.URL+"/accounts/transfer", "application/json", strings.NewReader(body))
			if err != nil {
				return
			}
			resp.Body.Close()
		}()
		go func() {
			defer wg.Done()
			body := fmt.Sprintf(`{"from_account_id":"%s","to_account_id":"%s","amount":10}`, accB.ID, accA.ID)
			resp, err := http.Post(server.URL+"/accounts/transfer", "application/json", strings.NewReader(body))
			if err != nil {
				return
			}
			resp.Body.Close()
		}()
	}

	wg.Wait()

	finalA := getAccount(t, server.URL, accA.ID)
	finalB := getAccount(t, server.URL, accB.ID)
	total := finalA.Balance + finalB.Balance

	if math.Abs(total-2000) > 0.01 {
		t.Errorf("balance invariant violated: A=%.2f B=%.2f total=%.2f (expected 2000)",
			finalA.Balance, finalB.Balance, total)
	}

	t.Logf("Final balances: A=%.2f B=%.2f total=%.2f", finalA.Balance, finalB.Balance, total)
}
