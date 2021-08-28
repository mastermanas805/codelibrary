#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int32_t main()
{
    int t,n,k,x;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        vector<pair<int,int>> p;
        for(int i=0; i<n;i++)
        {
            cin>>x;
            p.pb(mp(x,i));
        }

        sort(p.begin(),p.end());
        int i=0,ans = 0;;
        while(p[0].ff == p[i].ff)
        {
            if(p[i].ss >= k) ans++;
            i++;
        }

        cout<<ans<<endl;
    }
}