// https://leetcode.com/problems/maximum-score-of-a-good-subarray/

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
            nums.push_back(0);
            int mx = 0, i = 0, n = nums.size(), x, top;
            stack<int> s;
            while(i<n)
            {
                if(s.empty() || nums[i] > nums[s.top()]) s.push(i++);
                else
                {
                    top = s.top();
                    s.pop();
                    x = nums[top]*(s.empty()?i:i-s.top() - 1);
                    if(s.empty()? i > k: (s.top() < k && i > k))
                        mx = max(mx, x);
                }
            }

            return mx;
    }
};