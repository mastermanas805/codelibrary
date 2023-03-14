// https://leetcode.com/problems/edit-distance
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        int dp[n+1][m+1];
        for(int i=0;i<n+1;i++) dp[i][0] = i;
        for(int i=0;i<m+1;i++) dp[0][i] = i;

        for(int i=1;i<n+1;i++){
            for(int j=1;j<m+1;j++){
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = 1 + min({
                                            dp[i][j-1], //insertion
                                            dp[i-1][j], //deletion
                                            dp[i-1][j-1] //replace
                                        });
            }
        }
        
        return dp[n][m];
    }
};