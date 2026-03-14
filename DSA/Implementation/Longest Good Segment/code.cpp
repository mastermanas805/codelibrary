#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back

int binary(vector<int>& v, int f, int r, int k, int s)
{
    int mid, seg, mseg;
    while(f<r)
    {
        mid = (f+r)/2;
        if(f)  { seg = ceil((double)(v[r]-v[f])/s);  mseg = ceil((double)(v[mid]-v[f])/s); }
        else   { seg = ceil((double)v[r]/s);         mseg = ceil((double)v[mid]/s); }
         
        if(seg <= k) return r-f;

        if(mseg <= k) return mid-f;
        
        if(seg < k) return 0;

        if(mseg > k) {r = mid-1; continue;}

        else {r = r-1; continue;}
    }

    return 0;
}


int32_t main()
{
    int t,n,k,s,x;
    cin>>t;
    while(t--)
    {
        cin>>n>>k>>s;
        vector<int> v;
        v.reserve(n);
        cin>>x;
        v.pb(x);
        for(int i=1; i<n; i++) {cin>>x; v.pb(x+v[i-1]);}
        
        int mx = 0;
        for(int i=0;i<n;i++) { x = binary(v,i,n-1,k,s); if(x == n-1) continue; else mx = max(mx,x); }
        cout<<mx+1<<endl;
    }
}