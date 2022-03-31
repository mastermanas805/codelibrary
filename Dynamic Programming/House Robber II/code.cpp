class Solution {
public:
    int rob(vector<int>& nums) {
        
        int n = nums.size();
        if(n<2) return n? nums[0]:0;
        
        return max(robber(nums, 0,n-2), robber(nums, 1,n-1));
    }
    
    int robber(vector<int>& nums, int l, int r)
    {
        int pre,cur, temp;
        pre = cur = 0;
        for(int i=l; i<=r; i++)
        {
            temp = max(nums[i]+pre, cur);
            pre = cur;
            cur = temp;
        }
        
        return cur;
    }
};