//src = https://www.geeksforgeeks.org/subset-sum-problem-dp-25/
//exp hindi =   https://youtu.be/_gPcYovP7wc
#include<bits/stdc++.h> 
using namespace std; 

 // } Driver Code Ends
//User function template for C++

class Solution{   
public:
    bool isSubsetSum(int n, int a[], int sum){
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
        
        return t[n][sum];
    }
};

// { Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        int N, sum;
        cin >> N;
        int arr[N];
        for(int i = 0; i < N; i++){
            cin >> arr[i];
        }
        cin >> sum;
        
        Solution ob;
        cout << ob.isSubsetSum(N, arr, sum) << endl;
    }
    return 0; 
} 
  // } Driver Code Ends