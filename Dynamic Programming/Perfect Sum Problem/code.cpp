class Solution{

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{

	public:
	int perfectSum(int a[], int n, int sum)
	{
	    int count = 0;
	    
        int t[n+1][sum+1];
        
        for(int i=0;i <n+1; i++) t[i][0] = 1;
        for(int i=1; i<sum+1; i++) t[0][i] = 0;
        
        for(int i=1; i<n+1; i++)
          for(int j=1; j<sum+1; j++)
           {
               if(a[i-1] <= j)
                 t[i][j] = t[i-1][j] + t[i-1][j-a[i-1]];
                 
               else
                 t[i][j] = t[i-1][j];
           }

         return t[n][sum];
	}
	  
};

// { Driver Code Starts.
int main() 
{
   	
   
   	int t;
    cin >> t;
    while (t--)
    {
        int n, sum;

        cin >> n >> sum;

        int a[n];
        for(int i = 0; i < n; i++)
        	cin >> a[i];

       

	    Solution ob;
	    cout << ob.perfectSum(a, n, sum) << "\n";
	     
    }
    return 0;
}
  // } Driver Code Ends