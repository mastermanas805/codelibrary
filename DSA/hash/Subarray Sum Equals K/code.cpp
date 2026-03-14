// https://leetcode.com/problems/subarray-sum-equals-k/

#include<bits/stdc++.h>

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int prefix = 0;
        map<int, int> mp;
        mp[0] = 1;
        int ans=0;
        for(int i:nums){
            prefix+=i;
            
            if(mp.find(prefix - k)!=mp.end()){
                ans+=mp[prefix - k];
            }

            auto itr = mp.find(prefix);
            int freq = 0;
            if(itr != mp.end()){
                freq = itr->second;
            }
            mp[prefix] = freq+1;
        }

        return ans;
    }
};