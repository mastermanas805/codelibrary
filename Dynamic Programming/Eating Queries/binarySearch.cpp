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

int candies(int p[], int &n, int &x)
{
    int l = 1, r = n, mid, ans = -1;

    while(l<=r)
    {
        mid = (l+r)/2;
        if(p[mid-1] >= x)
            {
                r = mid - 1;
                ans = mid;
            }
        else
            l = mid + 1;
    }

    return ans;
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n,q, x;
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        int c[n], p[n];
        for(int i=0;i<n;i++) cin>>c[i];
        sort(c , c + n, greater<int>());
        for(int i=0; i<n; i++) p[i] = (i?p[i-1]:0) + c[i];
        while(q--)
        {
            cin>>x;
            cout<<candies(p,n,x)<<endl;
        }
    }
}