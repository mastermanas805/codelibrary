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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int c[n];
        for(int i=0; i<n; i++) cin>>c[i];
        cin>>m;
        int cnt = 0, x;
        for(int i=0; i<m; i++) {    cin>>x; cnt+=x; }
        cout<<c[cnt%n]<<endl;
    }
}