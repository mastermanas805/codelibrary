#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int sol(int m, int n)
{
    vector<vector<int>> g(m+1);
    int x,y, regular = 0, special = 0;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for(int i=1; i<=m; i++){
        if(g[i].size() == 1) special++;
        else regular++;
    }

    return special*regular;
}

int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int t,m,n;
    cin>>t;
    while(t--)
    {
        cin>>m>>n;
        cout<<sol(m,n);

        cout<<"\n";
    }
}