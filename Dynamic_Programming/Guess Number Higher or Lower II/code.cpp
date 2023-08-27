// https://leetcode.com/problems/guess-number-higher-or-lower-ii/

#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> dp;
    
    int travel(int i ,int j){
        if(i >= j)
            return 0;
        if(dp[i][j] != -1)
                return dp[i][j];
        
        int ret = INT_MAX;
        for(int partition = i; partition<=j; partition++)
            ret = min(ret, partition + max( travel(i, partition -1) , travel(partition+1, j) ));
        
        return dp[i][j] = ret;
            
    }
    
    int getMoneyAmount(int n) {
        if(n == 1) return 0;
        
        dp.resize(n+1, vector<int>(n+1, -1));
        
        return travel(1,n);
    }
};