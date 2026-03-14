// https://leetcode.com/problems/distinct-subsequences/description/

#include<iostream>
using namespace std;

// Time Complexity: O(2^n)
// Space Complexity: O(1)
class RecursiveSolution {
public:

    int count(string s, string t, int i, int j){
        if(j<0) return 1;

        if(i<0) return 0;

        if(s[i] == t[j])
            return count(s,t,i-1,j-1) + count(s,t,i-1,j);
        
        return count(s,t,i-1,j);
    }

    int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();

        return count(s,t,m-1,n-1);
    }
};


// Time Complexity: O(m*n)
// Space Complexity: O(m*n)
class DPSolution {
public:
    int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();
        
        double dp[m+1][n+1];

        for(int i=0;i<=m;i++){
            for(int j=0;j<=n;j++){
                if(j == 0) dp[i][j] = 1;
                else if(i == 0) dp[i][j] = 0;
                else if(s[i-1] == t[j-1]){
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[m][n];
    }
};