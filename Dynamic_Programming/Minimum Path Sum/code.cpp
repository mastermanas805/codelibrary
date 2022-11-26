// https://leetcode.com/problems/minimum-path-sum/description/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));
        dp[0][1] = 0;
        for(int i=1; i<=m; i++)
            for(int j=1;j<=n; j++)
                dp[i][j] = grid[i-1][j-1] + min(dp[i-1][j] , dp[i][j-1]);
        return dp[m][n];
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