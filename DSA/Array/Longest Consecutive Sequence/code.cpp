// https://leetcode.com/problems/longest-consecutive-sequence/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int l = 1, mx = 1, x = 1, n = nums.size();
        
        if(n == 0) return 0;
        
        while(l<n)
        {
            if(nums[l-1]+1 == nums[l] ) x++;
            
            else if(nums[l-1] == nums[l]) {l++; continue;}
            
            else
                x = 1;
            mx = max(mx,x);
            l++;
        }
        
        return mx;
        
    }
};