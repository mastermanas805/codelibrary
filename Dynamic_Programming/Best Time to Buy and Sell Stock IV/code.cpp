class Solution {
public:
    vector<vector<vector<int>>> dp;
    vector<int>* prices;
    int n;

    int maxProfit(int k, vector<int>& prices) {
        this->prices = &prices;
        n = prices.size();
        dp.resize(n, vector<vector<int>>(k + 1, vector<int>(2, -1)));
        return maxProfit(0, true, k);
    }

    int maxProfit(int i, bool buy, int k) {
        if(i>=n || k <= 0) return 0;

        if(dp[i][k][buy] > -1) return dp[i][k][buy];

        if (buy == true) {
            return dp[i][k][buy] = max(-(*prices)[i] + maxProfit(i + 1, !buy, k),
                       0 + maxProfit(i + 1, buy, k));
        } else {
            return dp[i][k][buy] = max((*prices)[i] + maxProfit(i + 1, !buy, k - 1),
                       0 + maxProfit(i + 1, buy, k));
        }
    }
};