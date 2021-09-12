//src = https://leetcode.com/problems/maximal-rectangle/
//refrence = Online Stock Span
///hindi explanation - https://www.youtube.com/watch?v=St0Jf_VmG_g&list=PL_z_8CaSLPWdeOezg68SKkeLN4-T_jNHd&index=10

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
class Solution {
public:
    int mah(vector<int> v, int n)
    {
        vector<int> l,r,area;
        l.reserve(n), r.reserve(n), area.reserve(n);
        stack<int> s;
        int i;
        
        //nearest smallest to left
        i = 0;
        while(i<n)
        {
            while(!s.empty() && v[s.top()] >= v[i]) s.pop();
            if(s.empty()) l.pb(0);
            else l.pb(s.top()+1);
            s.push(i);
            i++;
        }
        
        while(!s.empty()) s.pop();
        
        //nearest smallest to right
        i = n-1;
        while(i >= 0)
        {
            while(!s.empty() && v[s.top()] >= v[i]) s.pop();
            if(s.empty()) r.pb(n-1);
            else r.pb(s.top()-1);
            s.push(i);
            i--;
        }
        
        reverse(r.begin(), r.end());
        
        //area
        int mx = 0;
        
        for(int i=0; i<n; i++) mx = max(mx, v[i]*(r[i] - l[i] +1));
        
        return mx;
    }
    
    int maximalRectangle(vector<vector<char>>& matrix) {
        int r = matrix.size();
        
        if(r == 0) return 0;
        
        int c = matrix[0].size();
        vector<vector<int>> a(r, vector<int>(c));
        
        for(int i=0; i<r; i++) 
            for(int j=0; j<c; j++) 
                a[i][j] = matrix[i][j] - '0';
        
        for(int i=1; i<r; i++) 
            for(int j=0; j<c; j++) 
                a[i][j] = (a[i][j] == 0)?0: a[i-1][j]+1;
        
        int mx = 0;
        for(int i=0; i<r; i++) mx = max(mx, this->mah(a[i], c));
        
        return mx;
    }
};