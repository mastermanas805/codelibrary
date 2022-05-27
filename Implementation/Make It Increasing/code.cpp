// https://codeforces.com/problemset/problem/1675/B
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
    int cnt = 0;
    bool f;
    for(int i=n-1; i>0; i--)
    {
        f = false;
        while(a[i-1] >= a[i])
        {
            a[i-1]/=2;
            cnt++;
            if(f) return -1;
            if(a[i-1] == 0) f = true;
        }
    }

    return cnt;
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t, n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        cout<<solve(a,n)<<endl;;
    }
}