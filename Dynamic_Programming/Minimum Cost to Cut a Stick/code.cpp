// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/
// https://takeuforward.org/data-structure/minimum-cost-to-cut-the-stick-dp-50/

#include <bits/stdc++.h>
using namespace std;
//////////////////Recursion////////////////////////////////////////////////////

class RecursiveSolution{
    int cut(int i, int j, vector<int> &cuts){
        if (i > j)
            return 0;
        
        int mn = INT_MAX;
        for(int index=i;index<=j;index++){
            int cost = cuts[j+1] - cuts[i-1] + cut(i, index-1, cuts) + cut(index+1, j, cuts);
            mn = min(mn, cost);
        }
        return mn;
    }

    int minCost(int n, vector<int> cuts){
        int c = cuts.size();
        cuts.push_back(n);
        cuts.push_back(0);
        sort(cuts.begin(), cuts.end());
        return cut(1,c,cuts);
    }
};

//////////////////DP-2DArray////////////////////////////////////////////////////

class MemoizationSolution{
    
    int minCost(int n, vector<int> cuts){
        int c = cuts.size();
        int dp[c+2][c+2];
        memset(dp, 0, sizeof(dp));
        for(int i=c;i>0;i--){
            for(int j=1;j<c1;j++){
                if(i>j) continue;
                int mn = INT_MAX;
                for(int ind=i; ind<=j; ind++){
                    int ans = cuts[j+1] - cuts[i-1] + dp[i][ind-1] + dp[ind+1][j];
                    mn = min(mn, ans);
                }
                dp[i][j] = mn;
            }
        }
        return dp[1][c];
    }
}