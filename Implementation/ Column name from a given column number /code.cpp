//https://practice.geeksforgeeks.org/problems/column-name-from-a-given-column-number4244/1/?company[]=Paytm&company[]=Paytm&difficulty[]=1&page=1&sortBy=newest&query=company[]Paytmdifficulty[]1page1sortBynewestcompany[]Paytm#editorial
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


class Solution{
    public:
    string colName (long long int n)
    {
        string s;
        char c;
        int x;
        while(n>0)
        {
            x = n%26;
            if(x == 0) x = 26, n--;
            c = 'A' + x -1;
            s = c + s;
            n=n/26;
        }
        
        return s;
    }
};

// { Driver Code Starts.
int main()
{
    int t; cin >> t;
    while (t--)
	{
		long long int n; cin >> n;
		Solution ob;
		cout << ob.colName (n) << '\n';
	}
}
  // } Driver Code Ends