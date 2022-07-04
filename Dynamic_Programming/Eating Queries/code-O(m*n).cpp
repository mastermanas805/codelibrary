#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }
#define mx 100000000

void memset(int a[][mx], int n, int m)
{
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m; j++)
            a[i][j] = INT_MAX;
}
void pre(int a[][mx], int c[], int n, int m)
{
    memset(a, n,m);

    for(int i=1; i<=n; i++) a[i][0] = 0;

    for(int i=1; i<=m; i++) if(i <= c[0])   a[1][i] = 1; 

    for(int i=2; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(j<=c[i-1])
                a[i][j] = 1;
            else
                a[i][j] = min(a[i-1][j], 1 + a[i-1][j - c[i-1]]);
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n,q, sum, x;
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        sum = 0;
        int c[n];
        for(int i=0;i<n;i++) { cin>>c[i]; sum+=c[i]; }
        int a[n+1][mx];
        pre(a, c, n, sum);

        for(int i=0;i<q; i++)
        {
            cin>>x;
            if(x <= sum)
                cout<<( a[n][x] == INT_MAX? -1: a[n][x]);
            else
                cout<<-1;
            
            cout<<endl;
        }
    }
}