// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define ff first
#define ss second
class Solution {
public:
    void merge(vector<pair<int,int>>& nums, vector<int>& count, int low, int mid, int high)
    {
        int j = mid+1;
        for(int i=low; i<=mid; i++)
        {
            while(j<=high && nums[i].ff > nums[j].ff) j++;
            count[nums[i].ss]+= (j-(mid+1));
        }
        
        vector<pair<int,int>> temp(high-low+1);
        int k = 0;
        
        int left = low, right = mid+1;
        while(left<=mid && right<=high)
        {
            if(nums[left].ff < nums[right].ff) temp[k++] = nums[left++];
            else temp[k++] = nums[right++];
        }
        
        while(left<=mid) temp[k++] = nums[left++];
        
        while(right<=high) temp[k++] = nums[right++];
        
        for(int i=low, j = 0; i<=high; i++, j++) nums[i] = temp[j];
        
    }
    
    void mergesort(vector<pair<int,int>>& nums, vector<int>& count, int low, int high)
    {
        if(low >= high) return;
        int mid = (low+high)/2;
        mergesort(nums, count, mid+1, high);
        mergesort(nums, count, low, mid);
        merge(nums,count,low,mid,high);
    }
    
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> count(nums.size(), 0);
        vector<pair<int,int>> v(nums.size());
        for(int i = 0; i<nums.size(); i++) v[i] = mp(nums[i], i);

        mergesort(v, count, 0, nums.size()-1);
        return count;
    }
};

int main()
{
    vector<int> v={5,2,6,1};
    Solution s;
    for(int i: s.countSmaller(v))  cout<<i<<" ";
}