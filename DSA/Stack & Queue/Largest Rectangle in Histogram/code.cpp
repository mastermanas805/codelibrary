//https://leetcode.com/problems/largest-rectangle-in-histogram/
class Solution {
public:
    int largestRectangleArea(vector<int>& h) {
        
        int sz = h.size();
        int ngl[sz], ngr[sz];
        stack<int> s;
        
        //nearest greatest to left
        for(int i=0;i<sz; i++)
        {
            while(!s.empty() && h[s.top()]>=h[i]) s.pop();
            
            if(s.empty()) ngl[i] = 0;
            else ngl[i] = s.top()+1;
            s.push(i);
        }
        
        while(!s.empty()) s.pop();
        
        //nearest greatest to right
        for(int i= sz-1; i>=0; i--)
        {
            while(!s.empty() && h[s.top()]>=h[i]) s.pop();
            
            if(s.empty()) ngr[i] = sz-1;
            else ngr[i] = s.top()-1;
            s.push(i);
        }
        
        
        int mx = -1;
        for(int i=0;i<sz; i++)
            mx = max(mx, h[i]*(ngr[i] - ngl[i] + 1));
        
        return mx;
    }
};