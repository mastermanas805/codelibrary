// https://leetcode.com/problems/burst-balloons

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dp[304][304];
    
    // Constructor to initialize the dp array with zeros
    Solution(){
        memset(dp, 0, sizeof(dp));
    }

    int maxCoins(vector<int>& nums) {
        // Adding 1 at the beginning and end of the nums array
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        
        // Call the recursive function count with appropriate indices
        return count(nums, 1, nums.size()-2);
    }

    int count(vector<int>& nums, int i, int j){
        int mx = -1;
        
        // Base case: if i is greater than j, return 0
        if(i > j) return 0;

        // Iterate through all possible positions to burst the balloon
        for(int k=i; k<=j; k++){
            // Calculate the result for the left subarray if not calculated already
            if(!dp[i][k-1])
                dp[i][k-1] = count(nums, i, k-1);
            
            // Calculate the result for the right subarray if not calculated already
            if(!dp[k+1][j])
                dp[k+1][j] = count(nums, k+1, j);

            // Calculate the cost of bursting the current balloon at position k,
            // considering the left and right subarray results, and the coins earned
            int cost = nums[i-1]*nums[k]*nums[j+1] + dp[i][k-1] + dp[k+1][j] ;
            
            // Update the maximum result
            mx = max(mx, cost);
        }

        return mx;
    }
};
