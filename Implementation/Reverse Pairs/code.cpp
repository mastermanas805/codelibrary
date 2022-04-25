#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int merge(vector<int>& nums, int low, int mid, int high)
    {
        int j = mid+1;
        int rev = 0;
        for(int i=low; i<=mid; i++)
        {
            while(j<=high && nums[i] > 2LL*nums[j]) j++;
            rev += (j-(mid+1));
        }
        
        vector<int> temp(high-low+1);
        int k = 0;
        
        int left = low, right = mid+1;
        while(left<=mid && right<=high)
        {
            if(nums[left] < nums[right]) temp[k++] = nums[left++];
            else temp[k++] = nums[right++];
        }
        
        while(left<=mid) temp[k++] = nums[left++];
        
        while(right<=high) temp[k++] = nums[right++];
        
        for(int i=low, j = 0; i<=high; i++, j++) nums[i] = temp[j];
        
        return rev;
    }
    
    int mergesort(vector<int>& nums, int low, int high)
    {
        if(low >= high) return 0;
        int mid = (low+high)/2;
        int inv = mergesort(nums, low, mid);
        inv += mergesort(nums,mid+1, high);
        inv += merge(nums,low,mid,high);
        return inv;
    }
    int reversePairs(vector<int>& nums) {
        return mergesort(nums, 0, nums.size()-1);
    }
};