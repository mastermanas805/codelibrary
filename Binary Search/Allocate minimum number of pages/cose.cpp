// { Driver Code Starts
// Initial template for C++

#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
//User function template in C++

class Solution 
{
    public:
    //Function to find minimum number of pages.
    int findPages(int a[], int n, int m) 
    {
        int l,r, mid, pages, x;
        l = r = 0;
        r = sum(a, n);
        l = max(a[0], a[n-1]);
        
        pages = -1;
        
        while(l<r)
        {
            mid = l + (r-l)/2;
            x = no_of_students(a,n,mid);
            if(x == m)
             {
                 pages = mid;
                 r = mid -1;
             }
            
            else if(x > m)
                l = mid + 1;
            else
                r = mid - 1;
        }
        
        return pages;
        
    }
    
    int no_of_students(int a[], int n, int mx)
    {
        int x = 0, students = 0;
        for(int i=0; i<n;)
        {
            students++;
            while(x+a[i] <= mx && i<n) x+=a[i++];
            x = 0;
        }
        return students;
    }

    int sum(int a[], int n)
    {
        int x = 0;
        for(int i=0; i<n; i++) x+=a[i];

        return x;
    }
};

// { Driver Code Starts.

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int A[n];
        for(int i=0;i<n;i++){
            cin>>A[i];
        }
        int m;
        cin>>m;
        Solution ob;
        cout << ob.findPages(A, n, m) << endl;
    }
    return 0;
}
  // } Driver Code Ends