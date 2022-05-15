#include<bits/stdc++.h>
using namespace std;
#define int long long


bool allocateCows(int a[], int &n, int &c,int &d)
{
    int p = a[0], cnt = 1;
    for(int i=1; i<n && cnt<=c; i++)
    {
        while(i<n && a[i]-p < d) i++;
        if(i >=n ) break;
        cnt++;
        p = a[i];
    }

    return cnt>=c?true:false;
}

int minDistance(int &n, int &c, int a[])
{
    sort(a,a+n);
    int l = 0, r = a[n-1], mid, cnt = 0;

    while(l<=r)
    {
        mid = (l+r)/2;
        if(allocateCows(a, n, c, mid))
            l = mid+1, cnt = max(cnt,mid);

        else
            r = mid - 1;
    }

    return cnt;
}

int32_t main()
{
    #ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    #endif

    int t,n,c;
    cin>>t;
    while (t--)
    {
        cin>>n>>c;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        cout<<minDistance(n,c,a)<<endl;
    }
}