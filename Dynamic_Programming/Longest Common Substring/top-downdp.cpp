/*
src = https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1
exp = https://youtu.be/HrybPYpOvz0
*/
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{
    public:
    vector<vector<int>> t;

    int longestCommonSubstr (string s1, string s2, int x, int y)
    {
        this->t = vector<vector<int>> (x+1, vector<int> (y+1,-1));
        int mx = 0;
        
        for(int i=0; i<x+1; i++)
          for(int j=0; j<y+1; j++)
            if(i == 0 || j == 0)
              t[i][j] = 0;
        
        for(int i=1; i<x+1; i++)
          for(int j=1; j<y+1; j++)
          {
              if(s1[i-1] == s2[j-1])
                t[i][j] = 1 + t[i-1][j-1];
              
              else
                t[i][j] = 0;
              
              mx = max(mx,t[i][j]);
          }
          
          
                    
          
          return mx;
    }
};

// { Driver Code Starts.

int main()
{
    int t; cin >> t;
    while (t--)
    {
        int n, m; cin >> n >> m;
        string s1, s2;
        cin >> s1 >> s2;
        Solution ob;

        cout << ob.longestCommonSubstr (s1, s2, n, m) << endl;
    }
}
// Contributed By: Pranay Bansal
  // } Driver Code Ends