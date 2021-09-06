//https://www.youtube.com/watch?v=NXOOYYwpbg4&list=PL_z_8CaSLPWdeOezg68SKkeLN4-T_jNHd&index=3
//https://www.geeksforgeeks.org/next-greater-element/

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find the next greater element for each element of the array.
    #define pb push_back
    vector<long long> nextLargerElement(vector<long long> arr, int n){
       stack<long long> s;
       int i = n-1;
       vector<long long> ans;
       
       while(i>=0)
       {
           while(!s.empty() && s.top()<=arr[i]) s.pop();
           
           if(s.empty()) ans.pb(-1);
           else ans.pb(s.top());
           
           s.push(arr[i]);
           i--;
       }
       
       reverse(ans.begin(), ans.end());
       return ans;
    }
};

// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        
        int n;
        cin>>n;
        vector<long long> arr(n);
        for(int i=0;i<n;i++)
            cin>>arr[i];
        
        Solution obj;
        vector <long long> res = obj.nextLargerElement(arr, n);
        for (long long i : res) cout << i << " ";
        cout<<endl;
    }
	return 0;
}  // } Driver Code Ends