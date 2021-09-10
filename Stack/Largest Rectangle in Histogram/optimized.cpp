//src = https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/329301/cpp-or-Faster-than-100
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int n = heights.size();
        stack<int> s;
        int area, maxArea = 0, i = 0;
        while(i < n){
            if(s.empty() || heights[i] > heights[s.top()]) s.push(i++);
            else
            {
                int top = s.top();
                s.pop();
                area = heights[top] * (s.empty() ? i : i - s.top() - 1);
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};