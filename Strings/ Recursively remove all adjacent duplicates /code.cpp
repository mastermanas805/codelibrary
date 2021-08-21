//https://practice.geeksforgeeks.org/problems/recursively-remove-all-adjacent-duplicates0744/1/?company[]=Paytm&company[]=Paytm&page=1&sortBy=newest&query=company[]Paytmpage1sortBynewestcompany[]Paytm
// { Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
//User function template for C++

class Solution{
public:
    string remove(string s){
        
        
        string ans = "";
        int sz = s.length(); Recursively remove all adjacent duplicates 
        int i,j;
        i = j = 0;
        for(int i=0; i<sz; i++)
        {
            j = i;
            while( i<sz && i+1 < sz && (s[i] == s[i+1]) ) i++;
            
            if(i == j) ans+=s[i];
        }
        
        if(s.length() != ans.length()) return remove(ans);
        
        return ans;
    }
};

// { Driver Code Starts.

int main() {
    int t;
    string tc;
    getline(cin, tc);
    t = stoi(tc);
    while (t--) {
        string s;
        getline(cin, s);
        Solution ob;
        cout << ob.remove(s) << "\n";
    }
    return 0;
}  // } Driver Code Ends