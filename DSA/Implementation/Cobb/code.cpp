#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int32_t main(){
    int t;
    cin>>t;
    while(t--)
    {
        int n,k,x;
        cin>>n>>k;
        vector<int> v;
        for(int i=0;i<n;i++) { cin>>x; v.pb(x); }

        int start = max((int)0 ,n-201);
        int ans = INT_MIN;
        for(int i=start;i<n;i++)
         for(int j=i+1;j<n;j++)
            ans = max(ans, (i+1)*(j+1) - k*(v[i]|v[j]) );
        
        cout<<ans<<endl;
    }
    return 0;
}

