#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


bool solve(int a[], int n, int m)
{ 
    sort(a, a+n);
    int cnt = 0;
     for(int i=0;i<n;i++)  
        cnt+= 1 + max(a[i%n], a[(i+1)%n]);
    
    return cnt <= m;
}


int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        cout<<(solve(a,n,m)?"yes":"no")<<endl;
    }
}