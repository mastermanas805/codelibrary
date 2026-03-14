class Trie {
public:
    bool flag = false;
    Trie* a[26];
    Trie() {
        flag = false;
        memset(a, NULL, sizeof(a));
    }

    void insert(string word) {
        insert(word, 0, word.size());
    }
    
    void insert(string word, int i, int n) {
        if(i >= n) {
            flag = true;
        } else if(a[word[i] - 'a'] == NULL) {
            a[word[i] - 'a'] = new Trie();
            a[word[i] - 'a']->insert(word, i+1, n);
        } else {
            a[word[i] - 'a']->insert(word, i+1, n);
        }
    }

    bool search(string word) {
        return search(word, 0, word.size());
    }
    
    bool search(string word, int i, int n) {
        if(i == n) {
            return flag;
        } else if(a[word[i] - 'a'] == NULL) {
            return false;
        } else {
            return a[word[i] - 'a']->search(word, i+1, n);
        }
    }
    
    bool startsWith(string prefix) {
        return startsWith(prefix, 0, prefix.size());
    }

    bool startsWith(string prefix, int i, int n) {
        if(i == n - 1 && a[prefix[i] - 'a'] != NULL) {
            return true;
        } else if(a[prefix[i] - 'a'] == NULL) {
            return false;
        } else {
            return a[prefix[i] - 'a']->startsWith(prefix, i+1, n);
        }

        return false;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */