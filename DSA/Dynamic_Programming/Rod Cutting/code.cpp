/*
src = https://practice.geeksforgeeks.org/problems/rod-cutting0840/1
hindi exp = https://www.youtube.com/watch?v=SZqAQLjDsag&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go&index=14

*/

class Solution{
  public:
    int cutRod(int p[], int n) {
        int dp[n+1][n+1];
        for(int i=0;i<=n;i++) dp[i][0] = dp[0][i] = 0;
        
        for(int i=1;i<=n;i++) //cut lentgth
            for(int j=1;j<=n;j++) //rod length
                if(i<=j)
                    dp[i][j] = max(dp[i-1][j], p[i-1] + dp[i][j-i]);
                else
                    dp[i][j] = dp[i-1][j];
        return dp[n][n];
    }
};