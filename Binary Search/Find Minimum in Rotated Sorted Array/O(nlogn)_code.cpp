/*
src = https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
hindi exp = https://www.youtube.com/watch?v=4WmTRFZilj8&list=PL_z_8CaSLPWeYfhtuKHj-9MpYb6XQJ_f2&index=7
*/

class Solution {
public:
    int n;
    int findMin(vector<int>& nums) {
        n = nums.size();
        return Bsearch_rotate(nums, 0, nums.size()-1);
         
    }
    
    int Bsearch_rotate(vector<int>& a, int l, int r)
    {
        if(r>=l)
        {
            int mid = l + (r-l)/2;
            
            if(a[(mid+1)%n]> a[mid] && a[(mid+n-1)%n] > a[mid]) return a[mid];
            
            if(a[r] < a[mid])  l = mid+1;
            
            else r = mid-1;
            
            return Bsearch_rotate(a, l, r);
        }
        
        return a[0];
    }
};