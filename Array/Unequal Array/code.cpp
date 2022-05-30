// https://codeforces.com/problemset/problem/1672/C
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int solve(int a[], int n)
{
    int i = 0, mn,mx;
    mn = INT_MAX;
    mx = 0;

    while(i<n-1)
    {
        if(a[i] == a[i+1])
        {
            mn = min(mn, i);
            mx = max(mx, i+1);
        }
        i++;
    }

    return mx-mn <2? 0: max((int)1, mx-mn + 1 -3);
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        cout<<solve(a, n)<<endl;
    }
}