// https://leetcode.com/problems/rotate-array
#include <bits/stdc++.h>
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
         k=k%nums.size();
        reverse(nums.begin(),nums.begin()+(nums.size()-k));

        reverse(nums.begin()+(nums.size()-k),nums.end());
    
        reverse(nums.begin(),nums.end());
    }
};