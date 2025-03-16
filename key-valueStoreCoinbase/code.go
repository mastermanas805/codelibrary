// https://leetcode.com/discuss/post/5843528/coinbase-sde3-remoteindia-sep-24-offer-b-v572/
package main

import (
	"fmt"
	"strings"
	"time"
)

type DataStore struct {
	data      map[string]entry
	undoStack []func()
	redoStack []func()
}

type entry struct {
	value  string
	expiry time.Time
}

func NewDataStore() *DataStore {
	return &DataStore{
		data: make(map[string]entry),
	}
}

func (ds *DataStore) get(key string) string {
	e, ok := ds.data[key]
	if !ok {
		return ""
	}
	if !e.expiry.IsZero() && time.Now().After(e.expiry) {
		ds.deleteKey(key) // Clean up expired keys on get.
		return ""
	}
	return e.value
}

func (ds *DataStore) set(key, value string, ttl int64) {
	oldValue := ds.get(key)
	oldExpiry := time.Time{}
	if e, ok := ds.data[key]; ok {
		oldExpiry = e.expiry
	}

	expiry := time.Time{}
	if ttl > 0 {
		expiry = time.Now().Add(time.Duration(ttl) * time.Second)
	}

	ds.data[key] = entry{value: value, expiry: expiry}

	undoFunc := func() {
		if oldValue == "" {
			ds.deleteKey(key)
		} else {
			ds.data[key] = entry{value: oldValue, expiry: oldExpiry}
		}
	}

	ds.undoStack = append(ds.undoStack, undoFunc)
	ds.redoStack = nil // Clear redo stack on new action.
}

func (ds *DataStore) deleteKey(key string) {
	oldValue := ds.get(key)
	oldExpiry := time.Time{}
	if e, ok := ds.data[key]; ok {
		oldExpiry = e.expiry
	}
	if oldValue == "" {
		return
	}

	delete(ds.data, key)

	undoFunc := func() {
		ds.data[key] = entry{value: oldValue, expiry: oldExpiry}
	}
	ds.undoStack = append(ds.undoStack, undoFunc)
	ds.redoStack = nil
}

func (ds *DataStore) update(key, value string, ttl int64) {
	if _, ok := ds.data[key]; !ok {
		return
	}
	ds.set(key, value, ttl)
}

func (ds *DataStore) scanKeys() []string {
	keys := []string{}
	for k := range ds.data {
		if ds.get(k) != "" { // Check for expiration
			keys = append(keys, k)
		}
	}
	return keys
}

func (ds *DataStore) scanKeysWithPrefix(prefix string) []string {
	keys := []string{}
	for k := range ds.data {
		if strings.HasPrefix(k, prefix) && ds.get(k) != "" {
			keys = append(keys, k)
		}
	}
	return keys
}

func (ds *DataStore) undo() {
	if len(ds.undoStack) > 0 {
		lastIndex := len(ds.undoStack) - 1
		undoFunc := ds.undoStack[lastIndex]
		undoFunc()
		ds.undoStack = ds.undoStack[:lastIndex]
		ds.redoStack = append(ds.redoStack, undoFunc)
	}
}

func (ds *DataStore) redo() {
	if len(ds.redoStack) > 0 {
		lastIndex := len(ds.redoStack) - 1
		redoFunc := ds.redoStack[lastIndex]
		redoFunc()
		ds.redoStack = ds.redoStack[:lastIndex]
		ds.undoStack = append(ds.undoStack, redoFunc)
	}
}

func main() {
	store := NewDataStore()

	store.set("key1", "value1", 0)
	store.set("key2", "value2", 5)

	fmt.Println("get(key1):", store.get("key1"))
	fmt.Println("get(key2):", store.get("key2"))

	store.update("key1", "new_value1", 0)
	fmt.Println("get(key1):", store.get("key1"))

	store.deleteKey("key2")
	fmt.Println("get(key2):", store.get("key2"))

	fmt.Println("scanKeys():", store.scanKeys())

	store.set("prefix_test1", "value", 0)
	store.set("prefix_test2", "value", 0)

	fmt.Println("scanKeysWithPrefix(prefix_):", store.scanKeysWithPrefix("prefix_"))

	store.undo()
	fmt.Println("scanKeys():", store.scanKeys())

	store.redo()
	fmt.Println("scanKeys():", store.scanKeys())

	time.Sleep(6 * time.Second)                               // Let key2 expire
	fmt.Println("get(key2) after expiry:", store.get("key2")) // Should be ""
}
