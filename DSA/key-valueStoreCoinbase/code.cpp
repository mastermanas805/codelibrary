#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <stack>
#include <algorithm>
using namespace std;

class InMemoryDataStore
{
private:
    unordered_map<string, pair<string, chrono::time_point<chrono::system_clock>>> data;
    stack<function<void()>> undoStack;
    stack<function<void()>> redoStack;

    // Helper Function to check if a key has expired
    bool isExpired(const string &key)
    {
        auto it = data.find(key);
        if (it != data.end() && it->second.second != chrono::time_point<chrono::system_clock>::min())
        {
            auto now = chrono::system_clock::now();
            if (now > it->second.second)
            {
                return true;
            }
        }
        return false;
    }

public:
    // Part 1: Basic Key-Value Store
    string get(const string &key)
    {
        if (isExpired(key))
        {
            deleteKey(key);
            return "";
        }

        auto it = data.find(key);
        if (it != data.end())
        {
            return it->second.first;
        }
        return "";
    }

    void set(const string &key, const string &value, long long ttl = -1)
    {
        string oldValue = get(key); // used for undo
        chrono::time_point<chrono::system_clock> expiryTime = chrono::time_point<chrono::system_clock>::min();

        if (ttl > 0)
        {
            expiryTime = chrono::system_clock::now() + chrono::seconds(ttl);
        }

        data[key] = {value, expiryTime};

        undoStack.push([this, key, oldValue, ttl]()
                       {
            if (oldValue == "") {
                deleteKey(key);
            } else {
                set(key, oldValue, ttl);
            } });
        redoStack = stack<function<void()>>(); // clear redo stack when a new action is performed.
    }

    void deleteKey(const string &key)
    {
        string oldValue = get(key);
        if (oldValue == "")
        {
            return;
        }

        chrono::time_point<chrono::system_clock> oldExpiry = data[key].second;
        data.erase(key);

        undoStack.push([this, key, oldValue, oldExpiry]()
                       { data[key] = {oldValue, oldExpiry}; });
        redoStack = stack<function<void()>>();
    }

    void update(const string &key, const string &value, long long ttl = -1)
    {
        if (data.find(key) == data.end())
        {
            return;
        }
        set(key, value, ttl);
    }

    // Part 2: Key Scanning
    vector<string> scanKeys()
    {
        vector<string> keys;
        for (const auto &pair : data)
        {
            if (isExpired(pair.first))
            {
                deleteKey(pair.first);
            }
            else
            {
                keys.push_back(pair.first);
            }
        }
        return keys;
    }

    vector<string> scanKeys(const string &prefix)
    {
        vector<string> keys;
        for (const auto &pair : data)
        {
            if (pair.first.rfind(prefix, 0) == 0 && !isExpired(pair.first))
            {
                keys.push_back(pair.first);
            }
        }
        return keys;
    }

    // Part 3: Time-to-Live (TTL)
    void set(string &key, string &value, long long ttl)
    {
        set(key, value, ttl);
    }

    void update(string &key, string &value, long long ttl)
    {
        update(key, value, ttl);
    }

    // Part 4: Undo/Redo
    void undo()
    {
        if (!undoStack.empty())
        {
            auto operation = undoStack.top();
            operation();
            undoStack.pop();
            redoStack.push(operation);
        }
    }

    void redo()
    {
        if (!redoStack.empty())
        {
            auto operation = redoStack.top();
            operation();
            redoStack.pop();
            undoStack.push(operation);
        }
    }
};

int main()
{
    InMemoryDataStore store;

    // Example usage
    store.set("key1", "value1");
    store.set("key2", "value2", 5); // TTL of 5 seconds
    cout << "get(key1): " << store.get("key1") << endl;
    cout << "get(key2): " << store.get("key2") << endl;

    store.update("key1", "new_value1");
    cout << "get(key1): " << store.get("key1") << endl;

    store.deleteKey("key2");
    cout << "get(key2): " << store.get("key2") << endl;

    cout << "scanKeys(): ";
    for (const auto &key : store.scanKeys())
    {
        cout << key << " ";
    }
    cout << endl;

    store.set("prefix_test1", "value");
    store.set("prefix_test2", "value");

    cout << "scanKeys(prefix_): ";
    for (const auto &key : store.scanKeys("prefix_"))
    {
        cout << key << " ";
    }
    cout << endl;

    store.undo();
    cout << "scanKeys(): ";
    for (const auto &key : store.scanKeys())
    {
        cout << key << " ";
    }
    cout << endl;
    store.redo();
    cout << "scanKeys(): ";
    for (const auto &key : store.scanKeys())
    {
        cout << key << " ";
    }
    cout << endl;
    return 0;
}