/*
src = https://practice.geeksforgeeks.org/problems/number-of-occurrence2259/1
reference  = https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/
hindi exp = https://www.youtube.com/watch?v=Ru_HhBFV3Xo&list=PL_z_8CaSLPWeYfhtuKHj-9MpYb6XQJ_f2&index=6
*/

#include<bits/stdc++.h>

using namespace std;


 // } Driver Code Ends
//User function template for C++
class Solution{
public:	
	/* if x is present in arr[] then returns the count
		of occurrences of x, otherwise returns 0. */
	int count(int arr[], int n, int x) {
	    return BsearchCount(arr, n, 0,n-1, x);
	}
	
	int BsearchCount(int a[], int n, int l, int r, int t)
	{
	    if(r>=l)
	    {
	        int mid = l + (r-l)/2;
	        if(a[mid] == t)
	        {
	            int count = 1;
	            for(int i=mid+1; a[i] == t && i<n; i++)
	                count++;
	            
	            for(int i=mid-1; a[i] == t && i>=0 ; i--)
	                count++;
	           return count;
	        }
	        
	        else if(t < a[mid]) r = mid-1;
	        
	        else l = mid+1;
	        
	        return BsearchCount(a,n,l,r,t);
	        
	    }
	    return 0;
	}
};

// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        Solution ob;
        auto ans = ob.count(arr, n, x);
        cout << ans << "\n";
    }
    return 0;
}
  // } Driver Code Ends