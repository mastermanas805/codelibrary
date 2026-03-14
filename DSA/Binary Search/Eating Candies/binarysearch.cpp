#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int binary_search(int a[], int n, int x)
{
    int l = 0, r = n, mid;
    while(l<=r)
    {
        mid = (l+r)/2;
        if(a[mid] == x) return mid;

        if(a[mid] > x) r = mid -1;
        else l = mid + 1;
    }

    return -1;
}
int solve(int a[], int n)
{
    if(n == 1) return 0;
    
    int mx = 0, i = 0, sz;
    if(n%2 == 0) sz = n/2; else sz = n/2 + 1;
    int l[sz], r[sz];

    for(i=0; i<sz; i++)  l[i] = a[i] + (i? l[i-1]: 0);
    
    for(i=0; i<sz; i++)  r[i] = a[n-1-i] + (i? r[i-1]: 0);
    
    for(i=0; i<sz; i++)
    {
        int j = binary_search(r, sz-1, l[i]);
        if(j != -1 && !( n%2 > 0 && i == j && i == sz-1))
            {
                mx = max(mx, i + 1 + j + 1);
            }
    }
    
    return mx;
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

        cout<<solve(a,n)<<endl;
    }
}