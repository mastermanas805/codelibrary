/*
src = https://leetcode.com/problems/partition-equal-subset-sum/
hindi exp = https://youtu.be/UmMh7xp07kY
time = sum*n
space = sum*n
*/

#include<bits/stdc++.h>
class Solution {
public:
    bool canPartition(vector<int>& a) {
        int n = a.size(), sum = accumulate(a.begin(),a.end(),0);
        
        if(sum%2) return 0;
        
        int t[n+1][sum+1];
        
        //when size of knap = 0
        for(int i=0; i<n+1; i++) t[i][0] = true;
        //when no of items is 0 and size of knap is not zero
        for(int j=1; j<sum+1; j++) t[0][j] = false;
        
        for(int i=1; i<n+1; i++)
          for(int j=1; j<sum+1; j++)
          {
              if(a[i-1] <= j)
                t[i][j] = (t[i-1][j]) || (t[i-1][j-a[i-1]]);
              
              else if(a[i-1] > j)
                t[i][j] = t[i-1][j];
          }
        
        return t[n][sum/2];
    }
};