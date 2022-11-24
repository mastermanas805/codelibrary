// https://leetcode.com/problems/cherry-pickup-ii/

class Solution {
public:
    int dp[70][70][70];
    int solve(vector<vector<int>>& g, int n, int m, int r, int c1, int c2){
        if(c1<0 || c2<0 || c1>=m || c2>=m){
            return INT_MIN;
        }
        if(r==n) return 0;

        if(dp[r][c1][c2] != -1) return dp[r][c1][c2];

        int mx = 0;
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++)
                mx = max(mx, solve(g,n,m,r+1,c1+i,c2+j));
        
        return dp[r][c1][c2] = mx + (c1 == c2? g[r][c1]: g[r][c1] + g[r][c2]);
            
    }
    int cherryPickup(vector<vector<int>>& g) {
        int n = g.size(), m = g[0].size();
        memset(dp,-1, sizeof(dp));
        return solve(g,n,m,0,0,m-1);
    }
};