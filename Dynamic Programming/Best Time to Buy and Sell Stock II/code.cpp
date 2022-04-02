//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy, sell, profit, n = prices.size();
        profit = buy = 0;
        sell = 1;
        
        while(sell < n)
        {
            if(prices[sell-1] > prices[sell])
            {
                profit+=prices[sell-1] - prices[buy];
                buy = sell;
            }
            
            if(prices[sell] < prices[buy]) buy = sell;
            
            sell++;
        }
        
        if(prices[sell-1] > prices[buy])
        {
            profit+=prices[sell-1] - prices[buy];
        }

        return profit;
    }
};