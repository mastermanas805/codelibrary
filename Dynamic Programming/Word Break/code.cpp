/*
https://leetcode.com/problems/word-break/
*/
#define mx 301
class Solution {
public:
    
    bool check(bool a[mx][mx], int f, int r)
    {
        for(int i=f; i<r; i++)
            if(a[f][i] && a[i+1][r]) return 1;
        return 0;
    }
    
    bool wordBreak(string s, vector<string>& d) {
        int n = s.length()+1,i,j;
        set<string> f(d.begin(), d.end());
        bool a[mx][mx];
        memset(a,0,sizeof(a));
        
        for(int x=0; x<n; x++)
            for(int y=1; y<=n && n-(y+x)>=0; y++)
            {
                i = y, j = x+y;
                if(f.find(s.substr(i-1,j-i+1)) != f.end())
                    a[i][j] = 1;
                else if(check(a,i,j))
                    a[i][j] = 1;
                
            }
        
        return a[1][n];
    }
};