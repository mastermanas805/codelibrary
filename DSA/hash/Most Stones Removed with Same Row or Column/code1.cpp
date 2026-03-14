#include <bits/stdc++.h>
using namespace std;
// Data Structure ->
//   1. Add Word
//   2. Remove Word
//   3. Get Kth Highest Frequent Word
  

class TopKWords {
    public:
    unordered_map<string, int> word_freq;
    unordered_map<int, unordered_set<string>> freq_bucket;
    
    int mx_freq;
    TopKWords(): mx_freq(0) {};
    
    void add(string word) {
        int old_freq = word_freq[word];
        int new_freq = old_freq + 1;
        
        if(old_freq > 0) {
            freq_bucket[old_freq].erase(word);
            if(freq_bucket[old_freq].empty()) {
                freq_bucket.erase(old_freq);
            }
        }
        
        word_freq[word] = new_freq;
        freq_bucket[new_freq].insert(word);
        
        if(new_freq > mx_freq) {
            mx_freq = new_freq;
        }
    }
    
    void remove(string word) {
        if(word_freq.find(word) == word_freq.end()) {
            return;
        }
        
        int old_freq = word_freq[word];
        freq_bucket[old_freq].erase(word);
        
        if(freq_bucket[old_freq].empty()) {
            freq_bucket.erase(old_freq);
            if(old_freq == mx_freq) {
                mx_freq--;
            }
        }
        
        int new_freq = old_freq - 1;
        if(new_freq > 0){
            word_freq[word] = new_freq;
            freq_bucket[new_freq].insert(word);
        } else {
            word_freq.erase(word);
        }
    }
    
    
    string getKHighest(int k) {
        if(k<=0) return "";
        
        int curr_freq = mx_freq;
        int words_counted = 0;
        int freq = 0;
        while(curr_freq >0 && freq <= k) {
            if(freq_bucket.find(curr_freq)  != freq_bucket.end()) {
                freq+=freq_bucket[curr_freq].size();
                if(freq>=k)
                    return *freq_bucket[curr_freq].begin();
            }
            curr_freq--;
        }
        
        return "";
    }
};

int main()
{
    TopKWords obj;
    obj.add("hello");
    obj.add("hello");
    obj.add("hello");
    obj.add("world");
    obj.add("earth");
    
    cout<<obj.getKHighest(2);

    return 0;
}