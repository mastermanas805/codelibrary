// https://leetcode.com/problems/lru-cache/

#include<bits/stdc++.h>

// Define a structure for the linked list nodes
struct Node {
    int key;
    int val;
    Node *next;
    Node *prev;
    Node(int key, int val) : key(key), val(val), next(nullptr), prev(nullptr) {}
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, Node*> data;  // A map to store key-node pairs

    Node *head = new Node(-1, -1);  // Dummy head node for easy insertion
    Node *tail = new Node(-1, -1);  // Dummy tail node for easy deletion

    LRUCache(int capacity) {
        this->capacity = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    // Retrieve the value of a key
    int get(int key) {
        if(data.find(key) == data.end()){
            return -1;  // Key not found
        }
        Node *node = data[key];
        remove(node);  // Move the accessed node to the front
        add(node);
        return node->val;  // Return the value associated with the key
    }
    
    // Insert or update a key-value pair
    void put(int key, int value) {
        if (data.find(key) != data.end()) {
            Node *oldNode = data[key];
            remove(oldNode);  // Remove the old node from the linked list
        }
        
        Node *node = new Node(key, value);  // Create a new node
        data[key] = node;  // Update the map with the new node
        add(node);  // Add the new node to the front
        
        if (data.size() > capacity) {
            Node *nodeToDelete = tail->prev;
            remove(nodeToDelete);  // Remove the least recently used node
            data.erase(nodeToDelete->key);  // Remove the corresponding entry from the map
        }
    }

    // Remove a node from the linked list
    void remove(Node* node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Add a node to the front of the linked list
    void add(Node* node){
        node->next = head->next;
        head->next = node;
        node->prev = head;
        node->next->prev = node;
    }
};

// Main function for testing
int main() {
    // Create an LRUCache object with a capacity of 2
    LRUCache cache(2);

    // Perform example operations
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;  // Output: 1
    cache.put(3, 3);
    cout << cache.get(2) << endl;  // Output: -1 (not found)
    cache.put(4, 4);
    cout << cache.get(1) << endl;  // Output: -1 (not found)
    cout << cache.get(3) << endl;  // Output: 3
    cout << cache.get(4) << endl;  // Output: 4

    return 0;
}
