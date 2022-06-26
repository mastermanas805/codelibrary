//https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        
        int l,r, n = nums.size(), mx = 0,a,b,x,y;
        a = b = 0;
        x = y = n-1;
        l = r = 0;
        
        for(int i=0; i<n; i++)
            if(nums[i] > 0) nums[i] = 1;
            else if(nums[i] < 0) nums[i] = -1;
        
        for(int i=0; i<n; i++)
        {   
            
            l = (l?l:1) * nums[i], b++;
            r = (r?r:1) * nums[n - 1 - i], y--;
            
            if(l == 0) a = i+1;
            if(r == 0) x = n-1-i-1;
            
            if(l > 0)
                mx = max(mx, abs(a-b));
            if(r > 0)
                mx = max(mx, abs(x-y));
        }
        
        return mx;
    }
};