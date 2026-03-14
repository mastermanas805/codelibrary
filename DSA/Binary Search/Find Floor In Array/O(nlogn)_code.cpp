// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution{
#define ll long long
  public:
    // Function to find floor of x
    // n: size of vector
    // x: element whose floor is to find
    int fl=-1;
    int findFloor(vector<ll> v, ll n, ll x){
        this->bsearch(v,0,n-1,x);
        return this->fl;
    }
    
    void bsearch(vector<ll>& v, ll l, ll r, ll x)
    {
        if(r>=l)
        {
            int mid = l + (r-l)/2;
            if(v[mid] == x)
            {
                this->fl = mid;
                return;
            }
            
            if(v[mid] < x)
            {
                this->fl = mid;
                l = mid+1;
            }
            
            else r = mid - 1;
            
            bsearch(v,l,r,x);
        }
    }
};


// { Driver Code Starts.

int main() {
	
	long long t;
	cin >> t;
	
	while(t--){
	    long long n;
	    cin >> n;
	    long long x;
	    cin >> x;
	    
	    vector<long long> v;
	    
	    for(long long i = 0;i<n;i++){
	        long long temp;
	        cin >> temp;
	        v.push_back(temp);
	    }
	    Solution obj;
	    cout << obj.findFloor(v, n, x) << endl;
	   
	}
	
	return 0;
}  // } Driver Code Ends