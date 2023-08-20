// https://leetcode.com/problems/shortest-common-supersequence
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {
         int n=s1.length();
        int m=s2.length();
        vector<vector<int>> dp(n+1,vector<int>(m+1,-1));
        for(int i=0;i<=n;i++){
            dp[i][0] = 0;
        }
        for(int i=0;i<=m;i++){
            dp[0][i] = 0;
        }
        
        for(int ind1=1;ind1<=n;ind1++){
            for(int ind2=1;ind2<=m;ind2++){
                if(s1[ind1-1]==s2[ind2-1])
                    dp[ind1][ind2] = 1 + dp[ind1-1][ind2-1];
                else
                    dp[ind1][ind2] = 0 + max(dp[ind1-1][ind2],dp[ind1][ind2-1]);
            }
        }
        int i=n,j=m;
        string s="";
        while(i>0 && j>0){
            if(s1[i-1]==s2[j-1]){
                s+=s1[i-1];
                i--;
                j--;
            }
            else if(dp[i-1][j]>dp[i][j-1]){
                s+=s1[i-1];
                i--;     
            }
            else{
                s+=s2[j-1];
                j--;
            }
        }
        cout<<s;
        while(i>0){
            s+=s1[i-1];
            i--;
        }
        while(j>0){
            s+=s2[j-1];
            j--;
        }
        reverse(s.begin(),s.end());
        return s;
    }
};