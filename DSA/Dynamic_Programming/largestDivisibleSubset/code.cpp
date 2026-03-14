#include <bits/stdc++.h>
using namespace std;

vector<int> largestDivisibleSubset(vector<int> nums) {
        if(nums.empty()) return {};
        if(nums.size() == 1) return nums;
        
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> parent(n, -1);
        
        // DP: dp[i] = length of largest divisible subset ending at nums[i]
        for(int i = 1; i < n; i++) {
            for(int j = i - 1; j >= 0; j--) {
                // Only check if nums[i] is divisible by nums[j] (array is sorted)
                if((nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0) && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
        
        // Find index with maximum subset length
        int maxIdx = 0;
        for(int i = 1; i < n; i++) {
            if(dp[i] > dp[maxIdx]) {
                maxIdx = i;
            }
        }
        
        // Reconstruct result using parent pointers
        vector<int> result;
        while(maxIdx != -1) {
            result.push_back(nums[maxIdx]);
            maxIdx = parent[maxIdx];
        }
        reverse(result.begin(), result.end());
        
        return result;
    }

int main()
{
    for(auto i: largestDivisibleSubset({5,9,18,54,108,540,90,180,360,720}))
        cout << i << " ";

    return 0;
}