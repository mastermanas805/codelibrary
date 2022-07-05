// { Driver Code Starts
#include <bits/stdc++.h>

using namespace std;

 // } Driver Code Ends
//User function template for C++
class Solution{
public:
	// Function to check if the
	// Pythagorean triplet exists or not
	bool checkTriplet(int arr[], int n) {
    
            sort(arr,arr+n);
            int l = 0, m = l + 1, r = m + 1;
            
            while(l<=n-3)
            {
                int a = arr[l], b = arr[m], c = arr[r];
                if((a*a) + (b*b) == (c*c))
                    return true;
                if(r != n-1)
                        r++;
                else if(m != n-2)
                    m++, r = m + 1;
                else
                    l++, m = l + 1, r = m + 1;
               
            }
            
            return false;
        }
};

// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, i;
        cin >> n;
        int arr[n];
        for (i = 0; i < n; i++) {
            cin >> arr[i];
        }
        Solution ob;
        auto ans = ob.checkTriplet(arr, n);
        if (ans) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
  // } Driver Code Ends