/*
src = https://practice.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/
hindi exp = https://youtu.be/2JSQIhPcHQg
*/
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
//User function template in C++

class Solution 
{
    public:
    //Function to find minimum number of pages.
    int books(vector<int> &a, int m);
};


bool ispossible(vector<int>& a, int n, int m, int curr_min)
{
    int students = 1;
    int sum = 0;

    for(int i=0; i<n; i++)
    {
        if(a[i] > curr_min) return false;

        if(sum + a[i] > curr_min)
        {
            students++;
            sum = a[i];
            if(students > m) return false;
        }

        else sum+=a[i];

    }

    return true;
}


int Solution::books(vector<int> &a, int m) {
    int n = a.size();
    if(n < m) return -1;
        
    int l,r, mid, pages, x;
    l = r = 0; //left and right
    r = accumulate(a.begin(), a.end(), 0); //dertermining maximum number of pages a person can read
    
    
    pages = -1;
    
    while(l<=r)
    {
        mid = (l+r)/2;
        if(ispossible(a, n, m, mid))
            {
                pages = mid;
                r = mid -1;
            }
        
        else
            l = mid + 1;
    }
    
    return pages;

}

// { Driver Code Starts.

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> A(n);
        for(int i=0;i<n;i++){
            cin>>A[i];
        }
        int m;
        cin>>m;
        Solution ob;
        cout << ob.books(A, m) << endl;
    }
    return 0;
}
  // } Driver Code Ends