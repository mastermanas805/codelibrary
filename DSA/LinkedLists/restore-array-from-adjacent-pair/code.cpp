#include <bits/stdc++.h>
using namespace std;
#define pb push_back
class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& ap) {
        
     map<int, bool> f;
     map<int, vector<int>> mp;

     int x = 0, j = 0;
     
        for(int i=0; i<ap.size(); i++)
        {
            f[ap[i][0]] = f[ap[i][1]] = 1;
            mp[ap[i][0]].pb(ap[i][1]);
            mp[ap[i][1]].pb(ap[i][0]);
        }

        for(auto i: mp)
           if(i.second.size() == 1)
              {
                  x = i.first;
                  break;
              }
            
        vector<int> v;
        stack<int> s;
        s.push(x);
        
        while(!s.empty())
        {
            x = s.top();
            s.pop();
            v.pb(x);
            f[x] = 0;
            
            
            for(auto i: mp[x])
                if(f[i])
                {
                    s.push(i);
                    f[i] = 0;
                }
        }
        
        return v;
    }
};


int main()
{
    Solution s;
    vector<vector<int>> v = {{-3,-9},{-5,3},{2,-9},{6,-3},{6,1},{5,3},{8,5},{-5,1},{7,2}};
    
    s.restoreArray(v);

    return 0;
}