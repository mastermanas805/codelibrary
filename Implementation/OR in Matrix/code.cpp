#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

void sol(){
    int n,m,s;
    cin>>n>>m;
    int a[n][m],b[n][m], r[n] = {0}, c[m] = {0};
    bool f = 0;
    s = 0;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>a[i][j], r[i] += a[i][j], c[j] += a[i][j];
    
    memset(b, 0, sizeof(b));
    for(int i=0;i<min(m,n);i++)
    {
        if(r[i] + c[i] == m+n)    b[i][i] = 1;
        else if(a[i][i] || (a[i][i] == 0 && r[i] + c[i] != 0)) s++;
    }

    if(s == min(m,n)) {cout<<"NO"<<endl;  return;}

    cout<<"YES"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout<<b[i][j]<<" ";
        cout<<endl;
    }
    
}


int32_t main()
{
    sol();
}