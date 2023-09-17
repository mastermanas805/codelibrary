// https://leetcode.com/problems/3sum-smaller/description/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int count(vector<int>& nums, int target,int l, int r){
        int ret = -1;

        while(l<=r){
            int mid = (l+r)/2;
            if(nums[mid] <target){
                ret = max(ret, mid);
                l = mid +1;
            }else{
                r = mid -1;
            }
        }
        return ret;
    }
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size();
        if(n<3) return 0;

        sort(nums.begin(), nums.end());

        int cnt = 0;
        for(int i=0;i<n-2;i++){
            for(int j=i+1;j<n-1;j++){
                int ind = count(nums, target-nums[i]-nums[j], j+1, n-1);
                if(ind!=-1)
                    cnt+=(ind - j );
            }
        }

        return cnt;
    }
};