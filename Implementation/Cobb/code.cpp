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
    while(t--){
        int n,k,x;
        cin>>n>>k;
        vector<pii> v;
        for(int i=0;i<n;i++) { cin>>x; v.pb(mp(x,i+1)); }
        sort(a,a+n,compare);
        cout<<sol(n,k,a)<<endl;
    }
    return 0;
}

