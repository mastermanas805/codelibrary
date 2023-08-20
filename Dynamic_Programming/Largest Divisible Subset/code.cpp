// https://leetcode.com/problems/largest-divisible-subset

// Time Complexity: O(n^2)
// Space Complexity: O(n)

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        pair<int,int> nxt[n];
        for(int i=n-1;i>=0;i--){
            pair<int,int> x = {0,-1};
            for(int j=i+1;j<n;j++){
                if(nums[j]%nums[i] == 0 && nxt[j].first > x.first)
                    x = {nxt[j].first, j};
            }
            x.first++;
            nxt[i] = x;
        }

        pair<int,int> mx = {0,0};
        for(int i=0;i<n;i++){
            if(nxt[i].first > mx.first)
                mx = {nxt[i].first, i};
        }

        int i = mx.second;
        vector<int> ret;
        while(i!=-1){
            ret.push_back(nums[i]);
            i = nxt[i].second;
        }

        return ret;
    }
};