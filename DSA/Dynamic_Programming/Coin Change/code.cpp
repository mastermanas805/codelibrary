//https://practice.geeksforgeeks.org/problems/number-of-coins1824/1/?company[]=Paytm&company[]=Paytm&difficulty[]=1&page=1&sortBy=newest&query=company[]Paytmdifficulty[]1page1sortBynewestcompany[]Paytm
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution
{
  public:
    long long int count( int S[], int m, int n, int i = 0)
    {
         long long int table[n+1];         
         // Initialize all table values as 0         
         memset(table, 0, sizeof(table));         
         // Base case (If given value is 0)         
         table[0] = 1;         
         // Pick all coins one by one and update the table[] values         
         // after the index greater than or equal to the value of the         
         // picked coin         
         for(long long int i=0; i<m; i++)         
         for(long long int j=S[i]; j<=n; j++)         
         table[j] += table[j-S[i]];         
         return table[n];
    }
};

// { Driver Code Starts.
int main()
{
    int t;
    cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		int arr[m];
		for(int i=0;i<m;i++)
		    cin>>arr[i];
	    Solution ob;
		cout<<ob.count(arr,m,n)<<endl;
	}
    
    
    return 0;
}  // } Driver Code Ends


///Memoization 1D DP////////////////

// https://leetcode.com/problems/coin-change/description/
#define mx 10001
class Solution {
public:
    int coinChange(vector<int> coins, int sum) {
        int n = coins.size(), dp[sum+1];
        memset(dp, mx, sizeof(dp));
        dp[0] = 0;
        for(int i=0;i<n;i++)
            for(int j=coins[i];j<=sum;j++)
                dp[j]= min(dp[j], 1 + dp[j-coins[i]]);
                
        return dp[sum] >= mx?-1:dp[sum];
    }
};