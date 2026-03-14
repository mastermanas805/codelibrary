// https://leetcode.com/problems/interleaving-string/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length(); 
        if(m+n != s3.length()) return 0;
        
        int dp[m+1][n+1];
        memset(dp, false, sizeof(dp));
        dp[m][n] = true;
        
        for(int i=m;i>=0;i--){
            for(int j=n;j>=0;j--){
                 if(i<m && s1[i] == s3[i+j] && dp[i+1][j] == true)
                     dp[i][j] = true;
                 else if(j<n && s2[j] == s3[i+j] && dp[i][j+1] == true)
                     dp[i][j] = true;
            }
        }
        
        return dp[0][0];
    }
};