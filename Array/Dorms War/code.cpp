#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int solve(int &n, string &s, int m, bool f[])
{
    int cnt = 0, i = 0, mx = 0, j = 0;
    for(i=0; i<n; i++)
        if(f[s[i] - 'a'])
            mx = max(mx, i - j), j = i;

        return mx;
}


int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n,m;
    string s;
    char c;
    cin>>t;

    while(t--)
    {
        cin>>n>>s>>m;
        bool f[26];
        memset(f,0, sizeof(f));
        for(int i=0; i<m;i++)
        {
            cin>>c;
            f[c -'a'] = 1;
        }

        cout<<solve(n,s,m,f)<<endl;
    }
}