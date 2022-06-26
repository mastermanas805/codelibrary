/******************************************************************************

src = https://leetcode.com/problems/target-sum/
sol_src = https://leetcode.com/problems/target-sum/discuss/97340/C%2B%2BPython-short-dp-solution

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int S)
    {
        int sum = 0;
        for (auto n : nums)
            sum += n;
        if ((sum + S) % 2 == 1 || S > sum || S < -sum)
            return 0;
        int newS = (sum + S) / 2;
        vector<int> dp(newS + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = newS; j >= nums[i]; --j)
            {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[newS];
    }
};

int main()
{
    vector<int> v = {0, 0, 0, 0, 0, 0, 0, 0, 1};
    int target = 1;
    Solution s;
    cout << s.findTargetSumWays(v, target);

    return 0;
}
