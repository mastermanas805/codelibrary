// https://leetcode.com/problems/triangle/

#define mx 2000
class Solution {
public:
    
    int solve(vector<vector<int>>& a,vector<vector<int>>& dp, int m, int i, int j){
        if(i == m)
            return 0;
        if(dp[i][j] != mx) return dp[i][j];
        
        dp[i][j] = a[i][j] + min( solve(a,dp,m,i+1,j) , solve(a,dp,m,i+1,j+1));
        
        return dp[i][j];
    }
    int minimumTotal(vector<vector<int>>& a) {
        int n = a.size();
        vector<vector<int>> v(n, vector<int>(n, mx));
        return solve(a, v, a.size(), 0, 0);
    }
};