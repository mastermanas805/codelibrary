/*
    src = https://practice.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/
*/

// { Driver Code Starts
#include<bits/stdc++.h>
const int mod=1e9+7;
using namespace std;

 // } Driver Code Ends
// function to find longest common subsequence

class Solution
{
    public:
    vector<vector<int>> v;
    //Function to find the length of longest common subsequence in two strings.
    int lcs(int x, int y, string s1, string s2)
    {
        this->v = vector<vector<int>> (x, vector<int> (y,-1));
        
        return cal(s1, s2,x,y);
        
    }
    
    int cal(string s1, string s2, int x, int y)
    {
        if(x == 0 || y == 0) return 0;
        
        if(v[x-1][y-1] != -1) return v[x-1][y-1];
        
        else if(s1[x-1] == s2[y-1]) v[x-1][y-1] =  cal(s1,s2,x-1,y-1) + 1;
        
        else v[x-1][y-1] =  max(cal(s1,s2,x,y-1), cal(s1,s2,x-1,y));
        
        return v[x-1][y-1];
    }
};


// { Driver Code Starts.
int main()
{
    int t,n,k,x,y;
    cin>>t;
    while(t--)
    {
        cin>>x>>y;          // Take size of both the strings as input
        string s1,s2;
        cin>>s1>>s2;        // Take both the string as input
        Solution ob;
        cout << ob.lcs(x, y, s1, s2) << endl;
    }
    return 0;
}
  // } Driver Code Ends