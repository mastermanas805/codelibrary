// https://leetcode.com/problems/continuous-subarray-sum/description/
// https://leetcode.com/problems/continuous-subarray-sum/solutions/2745390/c-two-sum-with-modulo-approach-100-time-192ms-95-space-112-3mb/

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Create a map to store the running sum remainder and its corresponding index
        // Initialize the map with a dummy entry (0, -1) to handle cases where the entire array is divisible by k
        unordered_map<int, int> remainderMap{{0, -1}};
        int sum = 0;
        
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            
            // If k is not zero, take the modulus of sum with k
            if (k != 0)
                sum %= k;
            
            // Check if the same remainder has been encountered before
            if (remainderMap.count(sum)) {
                // If the subarray length is at least 2, return true
                if (i - remainderMap[sum] > 1)
                    return true;
            } else {
                // Store the running sum remainder and its corresponding index
                remainderMap[sum] = i;
            }
        }
        
        // No subarray found
        return false;
    }
};
