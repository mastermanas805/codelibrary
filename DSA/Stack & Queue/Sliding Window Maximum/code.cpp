/*
src = https://leetcode.com/problems/sliding-window-maximum/
*/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
          vector<int> ans;
        for (int i=0; i<nums.size(); i++) {
            if (!dq.empty() && dq.front() == i-k) dq.pop_front();
            
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            
            dq.push_back(i);
            if (i>=k-1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};

int main()
{
    vector<int> v = {1,3,-1,-3,5,3,6,7};
    int k= 3;
    Solution s;
    for(auto i:s.maxSlidingWindow(v,k))  cout<<i<<" ";
}