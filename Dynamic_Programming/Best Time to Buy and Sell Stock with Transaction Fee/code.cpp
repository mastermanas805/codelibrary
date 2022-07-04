/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
*/
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if(n<2) return 0;
        
        vector<int> s0(n,0), s1(n,0);
        
        s0[0] = 0;
        s1[0] = -prices[0];
        
        for(int i=1; i<n; i++)
        {
            s0[i] = max(s0[i-1], s1[i-1] + prices[i] - fee);
            s1[i] = max(s1[i-1], s0[i-1] - prices[i]);
        }
        
        return max(s0[n-1], s1[n-1]);
    }
};