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
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;

        if(n == m && n!=0) cout<<1;
        else if(n == m && n == 0) cout<<0;
        else if((n+m)%2 == 0) cout<<2;
        else cout<<-1;
        cout<<endl;
    }
}