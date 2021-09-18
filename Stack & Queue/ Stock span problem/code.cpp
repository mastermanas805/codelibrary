/*
src - https://practice.geeksforgeeks.org/problems/stock-span-problem-1587115621/1
hindi explaination - https://www.youtube.com/watch?v=p9T-fE1g1pU&list=PL_z_8CaSLPWdeOezg68SKkeLN4-T_jNHd&index=7 
*/
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends


#define pb push_back
class Solution
{
    public:
    //Function to calculate the span of stockâ€™s price for all n days.
    vector <int> calculateSpan(int price[], int n)
    {
       vector<int> temp,ans;
       temp.reserve(n);
       ans.reserve(n);
       
       stack<int> s;
       int i=0;
       while(i<n)
       {
           //if stack already empty in begening i=0
           if(s.empty()) {temp.pb(i), s.push(i), i++; continue;} 
           
           while(!s.empty() && price[s.top()]<=price[i]) s.pop();
           //when stack becomes empty when finding leftmost greatest element
           if(s.empty()) temp.pb(0);
           else temp.pb(s.top()+1);
           s.push(i);
           i++;
       }
       
       
       for(int i=0; i<n; i++)  ans.pb(i - temp[i] + 1);
       
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
		int i,a[n];
		for(i=0;i<n;i++)
		{
			cin>>a[i];
		}
		Solution obj;
		vector <int> s = obj.calculateSpan(a, n);
		
		for(i=0;i<n;i++)
		{
			cout<<s[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
  // } Driver Code Ends