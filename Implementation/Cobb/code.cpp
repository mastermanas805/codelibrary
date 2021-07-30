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
        vector<pii> v;
        for(int i=0;i<n;i++) { cin>>x; v.pb(mp(x,i+1)); }
        vector<pair<int,int>> bitflag(log2(10e5)+1, mp(0,0));
        for(auto i: v)
        {
            x = bitcount(i.ff);
            if(i.ss > bitflag[x].ff) { bitflag[x].ss = bitflag[x].ff; bitflag[x].ff = i.ss;}
            else if(i.ss > bitflag[x].ss) { bitflag[x].ss = i.ss;}
        }
    }

    int ans = INT_MIN;
    for(int i=0; i<32; i++)
    {
        ans = max(ans, bitflag[i].ff*bitflag[i].ss - k* );
        for(int j=0; j<32; j++)
          {

          }
    }
    return 0;
}

