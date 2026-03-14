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
	int f = -1;
    int s = -1;

	int count(int arr[], int n, int x) {
	    int sz = n-1;
        fBsearch(arr, 0, sz, x);
        rBsearch(arr, 0 , sz, x);
        return s-f+1;
	}
	
	void fBsearch(int n[], int l, int r, int t)
    {
        
        if(r >= l)
        {
            int mid = l + (r-l)/2;
            
            if(n[mid] == t)
            {
                this->f = mid;
                r = mid - 1;
            }
            
            else if(t < n[mid]) r = mid-1;
            else l = mid+1;

            fBsearch(n,l,r,t);
        }    
    }

    void rBsearch(int n[], int l, int r, int t)
    {
        
        if(r >= l)
        {
            int mid = l + (r-l)/2;
            
            if(n[mid] == t)
            {
                this->s = mid;
                l = mid + 1;
            }
            
            else if(t < n[mid]) r = mid-1;
            else l = mid+1;

            rBsearch(n,l,r,t);
        }    
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