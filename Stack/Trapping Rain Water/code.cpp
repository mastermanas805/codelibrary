/*
src = https://leetcode.com/problems/trapping-rain-water/
ref = https://www.geeksforgeeks.org/trapping-rain-water/
hindi exp = https://youtu.be/FbGG2qpNp4U
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int sz = height.size();
        vector<int> mxl(sz),mxr(sz);
        
        mxl[0] = height[0];
        for(int i=1;i<sz; i++)
            mxl[i] = max(height[i], mxl[i-1]);
        
        mxr[sz-1] = height[sz-1];
        for(int i= sz-2; i>=0; i--)
            mxr[i] = max(height[i], mxr[i+1]);
        
        int count = 0;
        for(int i=0; i<sz; i++)
            count+= min(mxl[i],mxr[i]) - height[i];
        
        return count;
    }
};