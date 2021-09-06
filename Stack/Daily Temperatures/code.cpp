/*
src = https://leetcode.com/problems/daily-temperatures/
ref - ../ Next Greater Element I/code.cpp
*/
#define pb push_back
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
       stack<int> s;
        
       int i = t.size()-1;
       vector<int> ans;
       ans.reserve(i+1);
       
       while(i>=0)
       {
           while(!s.empty() && t[s.top()]<=t[i]) s.pop();
           
           if(s.empty()) ans.pb(-1);
           else ans.pb(s.top());
           
           s.push(i);
           i--;
       }
       
       reverse(ans.begin(), ans.end());
       for(i=0; i<t.size();i++) ans[i] = ans[i] == -1? 0: ans[i] - i;
       return ans;
    }
};