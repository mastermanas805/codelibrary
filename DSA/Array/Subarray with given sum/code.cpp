// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find a continuous sub-array which adds up to a given number.
    vector<int> subarraySum(int a[], int n, long long s)
    {
        int l =0, sum = 0, i =0 ;
        
        while(i<n && l<n)
        {
            if(sum > s) while(sum > s && l<n)  sum-=a[l++];
            else sum+=a[i++];
            
            if(sum == s) return {l+1,i};
        }
        
        while(sum > s){
            sum-=a[l++];
            if(sum == s) return {l+1,i};
        }
        return {-1};   
    }
}