// https://leetcode.com/problems/partition-array-for-maximum-sum

#include <bits/stdc++.h>
using namespace std;

// Recursive Solution
// Time Complexity: O(n*k)
// Space Complexity: O(n)
class Solution {
public:
    vector<int> dp;
    int partition(vector<int>& arr, int k, int n, int i){
        if(dp[i] != -1)
            return dp[i];
        int mx = 0;
        int ret = 0;

        for(int j=i; j<n && j< (i+k); j++){
            if(mx < arr[j])
                mx = arr[j];
            ret = max(ret, mx*(j-i+1) + partition(arr,k,n,j+1));
        }

        return dp[i] = ret;
    }

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        dp = vector<int>(arr.size()+1, -1);
        dp[arr.size()]  = 0;
        return partition(arr,k, arr.size(), 0);
    }
};


// Iterative Solution (Bottom Up)
// Time Complexity: O(n*k)
// Space Complexity: O(n)
class Solution {
public:
    vector<int> dp;
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        dp = vector<int>(arr.size()+1, -1);
        int n = arr.size();
        dp[arr.size()]  = 0;

        for(int i = n-1;i>=0;i--){
            int mx = -1;
            int ret = -1;
            for(int j=i; j<n && j< (i+k); j++){
                if(mx < arr[j])
                    mx = arr[j];
                ret = max(ret, mx*(j-i+1) + dp[j+1]);
            }

            dp[i] = ret;
        }
        return dp[0];
    }
};

