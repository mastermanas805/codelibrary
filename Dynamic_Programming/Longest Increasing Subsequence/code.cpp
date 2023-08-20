//  https://leetcode.com/problems/longest-increasing-subsequence/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int len[n];
        memset(len, 1, sizeof(len));

        for(int i=n-1;i>=0;i--){
            int l = 0;
            for(int j=i+1; j<n; j++){
                if( nums[i] < nums[j] )
                    l = max(l, len[j]);
            }
            len[i] = l + 1;
        }

        return *max_element(len, len + n);
    }
};