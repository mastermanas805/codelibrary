#include <bits/stdc++.h>
using namespace std;


int maxSquare(int n, int m, vector<vector<int>> mat){
    int dp[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(i==0||j==0)
                dp[i][j] = mat[i][j];
    
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++){
            if(mat[i][j] == 0)
                dp[i][j] = 0;
            else
                dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
        }
    int mx = 0;
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            mx = max(mx, dp[i][j]);
    return mx;
}