// https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/

#define key pair<int, int>
#define ff first
#define ss second

class Solution {
public:
    int longestSubarray(vector<int> nums, int limit) {
        priority_queue<key> mxPQ;
        priority_queue<key, vector<key>, greater<key>> mnPQ;
        int front = 0, rear = 0, len = 1, n = nums.size();
        mxPQ.push({nums[0], 0});
        mnPQ.push({nums[0], 0});
        while (rear < n) {
            while (mxPQ.top().ss < front)
                mxPQ.pop();

            while (mnPQ.top().ss < front)
                mnPQ.pop();

            if (mxPQ.top().ff - mnPQ.top().ff <= limit) {
                len = max(len, rear - front + 1);
                rear++;
                if (rear < n) {
                    mxPQ.push({nums[rear], rear});
                    mnPQ.push({nums[rear], rear});
                }
            } else {
                front++;
            }
        }

        return len;
    }
};