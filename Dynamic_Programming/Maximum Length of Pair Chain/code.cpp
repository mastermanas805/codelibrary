// https://leetcode.com/problems/maximum-length-of-pair-chain/description/

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end());
        int n = pairs.size();
        int dp[n+1], mx;
        for(int i=0;i<n+1;i++) dp[i] = 0;
        
        for(int i=1;i<n+1;i++){
            mx = 0;
            for(int j=0;j<i-1;j++)
                if(pairs[j][1] < pairs[i-1][0])
                    mx = max(mx, dp[j+1]);
            dp[i] = 1 + mx;
        }            
        return *max_element(dp, dp+n+1);
    }
};