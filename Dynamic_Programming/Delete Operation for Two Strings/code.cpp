// https://leetcode.com/problems/delete-operation-for-two-strings/description/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        int dp[n+1][m+1];
        for(int i=0;i<=n;i++) dp[i][0] = 0;
        for(int i=0;i<=m;i++) dp[0][i] = 0;
        
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        
        return n+m - 2*dp[n][m];
    }
};