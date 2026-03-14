// https://leetcode.com/problems/predict-the-winner/description/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> dp;
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        dp = vector<vector<int>>(n, vector<int>(n,-1));
        return MaxDiff(nums,0,nums.size()-1) >= 0;
    }

    int MaxDiff(vector<int>& nums, int l, int r){
        if(l == r)
            return nums[l];
        if(dp[l][r] != -1)
            return dp[l][r];
        return dp[l][r] = max( nums[l] - MaxDiff(nums, l+1, r), nums[r] - MaxDiff(nums, l, r-1) );
    }
};