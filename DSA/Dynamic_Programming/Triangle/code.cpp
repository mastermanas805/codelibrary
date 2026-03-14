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


/////Memoization//////////////
class Solution {
public:
    int minimumTotal(vector<vector<int>> triangle) {
        int n = triangle.size(),mn;
        int dp[n][n];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = triangle[0][0];
        for(int i=1;i<n;i++)
            for(int j=0;j<=i;j++){
                if(j<=(i+1)/2){
                    mn = min(j<i?dp[i-1][j]: INT_MAX, j-1>-1? dp[i-1][j-1]: INT_MAX);
                }else{
                    mn = min(dp[i-1][j-1], j<i? dp[i-1][j]: INT_MAX);
                }
                dp[i][j] = triangle[i][j] + mn;
            }
        return *min_element(dp[n-1], dp[n-1]+n);
    }
};