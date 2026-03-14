// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{

  public:
	int minDifference(int a[], int n)  { 
	    // Your code goes here
	    int sum = accumulate(a,a+n, 0);
	    bool t[n+1][sum+1];
	    
	    for(int i=0; i<n+1; i++) t[i][0] = 1;
	    
	    for(int i=1; i<sum+1; i++) t[0][i] = 0;
	    
	    
	    for(int i=1; i<n+1; i++)
	    {
	        for(int j=1; j<sum+1; j++)
	        {
	            if(a[i-1]<= j)
	                t[i][j] = t[i-1][j] || t[i-1][j - a[i-1]];
	            
	            else
	                t[i][j] = t[i-1][j];
	        }
	    }
	    
	    int res = INT_MAX;
	    for(int i=0; i<sum+1; i++)
	        if(t[n][i])
    	      res = min(res, abs(sum - 2*i));
    
        return res;
	} 
	
};


// { Driver Code Starts.
int main() 
{
   
   
   	int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        int a[n];
        for(int i = 0; i < n; i++)
        	cin >> a[i];

       

	    Solution ob;
	    cout << ob.minDifference(a, n) << "\n";
	     
    }
    return 0;
}  // } Driver Code Ends