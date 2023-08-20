// https://leetcode.com/problems/edit-distance
#include<bits/stdc++.h>
using namespace std;

// Time Complexity: O(3^m)
// Space Complexity: O(m)
class RecursiveSolution {
public:
    int count(string word1, string word2, int i, int j){
        if(i < 0)
            return j + 1;

        if(j < 0)
            return i + 1;

        if(word1[i] == word2[j])
            return count(word1, word2, i-1, j-1);

        // insert i , j-1
        // delete i-1, j
        // update i-1,j-1 
        
        return 1 + min({    count(word1, word2, i, j-1),  
                            count(word1, word2, i - 1, j), 
                            count(word1, word2, i-1, j-1)  });
    }

    int minDistance(string word1, string word2){
        return count(word1, word2, word1.length() - 1, word2.length() - 1);
    }

};


// Time Complexity: O(n*m)
// Space Complexity: O(n*m)
class DPSolution {
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