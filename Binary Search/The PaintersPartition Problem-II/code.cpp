// { Driver Code Starts
// driver code

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
//User function template for C++

class Solution
{
  public:
    
    bool ispossible(int a[], int n, int k, int mn)
    {
        int sum = 0, students = 1, mx = -1;
        for(int i=0; i<n; i++)
        {
            if(a[i] > mn) return 0;
            
            else if(sum + a[i] > mn)
            {
                mx=max(mx, sum);
                students++;
                sum = a[i];
                if(students > k) return 0;
            }
            
            else sum+=a[i];
            
        }
        
        mx=max(mx, sum);
        return true;
    }
    
    long long minTime(int arr[], int n, int k)
    {
       long long l,r,mid, pages = -1;
       l = arr[0];
       r = accumulate(arr, arr+n, 0);
       while(l<=r)
       {
           mid = (l+r)/2;
           if(ispossible(arr,n,k,mid))
           {
               pages = mid;
               r = mid -1;
           }
           
           else l = mid + 1;
       }
       
       return pages;
    }
};

// { Driver Code Starts.

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int k,n;
		cin>>k>>n;
		
		int arr[n];
		for(int i=0;i<n;i++)
		    cin>>arr[i];
		Solution obj;
		cout << obj.minTime(arr, n, k) << endl;
	}
	return 0;
}  // } Driver Code Ends