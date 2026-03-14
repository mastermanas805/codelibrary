// https://leetcode.com/problems/paint-house-iii/
class Solution {
    public:
        vector<vector<vector<int>>> dp;
        int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n,
                    int target) {
            dp = vector<vector<vector<int>>>(
                target + 1, vector<vector<int>>(n + 1, vector<int>(m + 1, -1)));
            int ret = minCost(houses, cost, m, n, target, -1, 0);
            return ret == INT_MAX ? -1 : ret;
        }
    
        int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n,
                    int target, int prev, int houseNo) {
            if (houseNo == m)
                return (target == 0) ? 0 : INT_MAX; // Ensure target == 0 at end
    
            if (target < 0)
                return INT_MAX; // If target neighborhoods exceeded, return invalid
    
            if (prev > -1 && dp[target][prev][houseNo] != -1)
                return dp[target][prev][houseNo];
    
            int mn = INT_MAX;
    
            // If house is already painted
            if (houses[houseNo] != 0) {
                int newTarget = (houses[houseNo] - 1 == prev) ? target : target - 1;
                return minCost(houses, cost, m, n, newTarget, houses[houseNo] - 1,
                               houseNo + 1);
            }
    
            // If house is not painted, try all colors
            for (int i = 0; i < n; i++) {
                if (i == prev) {
                    // Continue with the same neighborhood
                    int nextCost =
                        minCost(houses, cost, m, n, target, i, houseNo + 1);
                    if (nextCost != INT_MAX)
                        mn = min(mn, cost[houseNo][i] + nextCost);
                } else {
                    // Create a new neighborhood
                    int nextCost =
                        minCost(houses, cost, m, n, target - 1, i, houseNo + 1);
                    if (nextCost != INT_MAX)
                        mn = min(mn, cost[houseNo][i] + nextCost);
                }
            }
    
            if (prev != -1)
                dp[target][prev][houseNo] = mn;
            return mn;
        }
    };