  // } Driver Code Ends

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
// Function to return minimum number of jumps to end of array

class Solution{
  public:
    int minJumps(int arr[], int n){
        
        if(n == 1) return 0;
        
        int b[n],r = n-1;
        memset(b,-1,sizeof(b));
        int mn,mn_index;
        b[0] = -1;
        b[n-1] = 0;
        for(int i=n-2; i>=0; i--)
        {
            if(arr[i] - (n-i) >= 0) b[i] = 1;
            
            else
            {
                  mn = INT_MAX;
                  for(int j=i+1;j<n && j<=i+arr[i]; j++)
                      if(mn > b[j] && b[j] != -1) mn = b[j],mn_index = j;
                  if(mn != INT_MAX) b[i] = 1 + b[mn_index];
            }
        }
        
        return b[0];
    }
};


// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,i,j;
        cin>>n;
        int arr[n];
        for(int i=0; i<n; i++)
            cin>>arr[i];
        Solution obj;
        cout<<obj.minJumps(arr, n)<<endl;
    }
    return 0;
}
  // } Driver Code Ends