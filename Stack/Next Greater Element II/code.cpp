//src
//https://leetcode.com/problems/next-greater-element-ii/
/* --------------------------------*/
//pre-requisite
//https://github.com/mastermanas805/codelibrary/blob/master/Array/%20Next%20Greater%20Element%20I/code.cpp

#define pb push_back
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& arr) {
       stack<int> s;
       int i = arr.size() - 1;
       for(i;i>=0;i--) s.push(arr[i]);
       i = arr.size()-1;
       vector<int> ans;
       
       while(i>=0)
       {
           while(!s.empty() && s.top()<=arr[i]) s.pop();
           
           if(s.empty()) ans.pb(-1);
           else ans.pb(s.top());
           
           s.push(arr[i]);
           i--;
       }
       
       reverse(ans.begin(), ans.end());
       return ans;
    }

};