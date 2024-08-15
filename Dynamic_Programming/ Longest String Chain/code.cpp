bool compLen(const string& a, const string& b) {
        return a.length() < b.length();
    }
    
class Solution {
public:
    bool isPredecessor(const string& predecessor, const string& successor) {
        int m = predecessor.size(), n = successor.size();
        if(m + 1 != n) return 0;
        int x = 0, y = 0;
        while(y<n && x<m){
            x = predecessor[x] == successor[y] ? x+1: x;
            y++;
        }

        return x == m;
    }

    

    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), compLen);
        int n = words.size();
        vector<int> dp(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if( isPredecessor(words[i], words[j]) )
                    dp[i] = max(dp[i], 1 + dp[j]);
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};