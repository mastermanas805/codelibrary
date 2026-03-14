/*
src = https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

reference  = https://www.geeksforgeeks.org/find-first-and-last-positions-of-an-element-in-a-sorted-array/
hindi exp = https://www.youtube.com/watch?v=zr_AoTxzn0Y&list=PL_z_8CaSLPWeYfhtuKHj-9MpYb6XQJ_f2&index=5
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int f = -1;
    int s = -1;
    vector<int> searchRange(vector<int>& nums, int target) {
        int sz = nums.size()-1;
        fBsearch(nums, 0, sz, target);
        rBsearch(nums,0 , sz, target);
        return {f,s};
    }
    
    void fBsearch(vector<int>& n, int l, int r, int t)
    {
        
        if(r >= l)
        {
            int mid = l + (r-l)/2;
            
            if(n[mid] == t)
            {
                this->f = mid;
                r = mid - 1;
            }
            
            else if(t < n[mid]) r = mid-1;
            else l = mid+1;

            fBsearch(n,l,r,t);
        }    
    }

    void rBsearch(vector<int>& n, int l, int r, int t)
    {
        
        if(r >= l)
        {
            int mid = l + (r-l)/2;
            
            if(n[mid] == t)
            {
                this->s = mid;
                l = mid + 1;
            }
            
            else if(t < n[mid]) r = mid-1;
            else l = mid+1;

            rBsearch(n,l,r,t);
        }    
    }
};

int main()
{
    vector<int> v = {5,7,7,8,8,10};
    int t = 8;
    Solution s;
    s.searchRange(v,t);
}