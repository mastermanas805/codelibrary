//https://leetcode.com/problems/maximum-sum-circular-subarray/
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int sum, mx_so_far, mn_so_far, curr_mx, curr_mn, i;
        i = sum = curr_mx = curr_mn = 0;
        mx_so_far = INT_MIN;
        mn_so_far = INT_MAX;
        
        while(i<nums.size())
        {
            sum+=nums[i];
            curr_mx+=nums[i];
            curr_mn+=nums[i];
            
            
            mx_so_far = max(mx_so_far, curr_mx);
            mn_so_far = min(mn_so_far, curr_mn);
            
            if(curr_mx<0) curr_mx = 0;
            if(curr_mn > 0) curr_mn = 0;
            
            i++;
        }
        
        if(mx_so_far > 0 || sum - mn_so_far > 0)
            return max(mx_so_far, sum - mn_so_far );
        else 
            return *max_element(nums.begin(), nums.end());
    }
};