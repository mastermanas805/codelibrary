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

class Solution {
public:
    int dp[104][104];
    int minCost(int n, vector<int>& cuts) {
        sort(begin(cuts),end(cuts));
        cuts.insert(cuts.begin(),0);
        cuts.push_back(n);
        memset(dp,0,sizeof(dp));


        for(int l=cuts.size()-2;l>=0;l--){
            for(int r=2;r<cuts.size();r++){
                if(l+1>=r)continue;
                int cur=INT_MAX;
                for(int k=l+1;k<r;k++){
                    cur=min(cur,dp[l][k]+dp[k][r]+cuts[r]-cuts[l]);
                }
                dp[l][r]=cur;
            }
        }
        return dp[0][cuts.size()-1];
    }
};