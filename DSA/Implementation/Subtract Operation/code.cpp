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
    if(n == 1) return a[0] == m;

    sort(a, a+n);
    int i=0, j = 1;

    while(i<n && j<n)
    {
        if(a[i] + m == a[j]) return true;
        if(a[i] + m < a[j]) i++;
        else j++;
    }

    return 0;
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