#include<bits/stdc++.h>
using namespace std;
#define int long long

int solve(int a[], int n)
{
    if(n == 1) return 0;
    
    int mx = 0, i = 0, l[n], r[n], low = 0, high = n-1;

    for(i=0; i<n; i++) l[i] = a[i] + (i?l[i-1]:0);

    for(i=n-1; i>=0; i--) r[i] = a[i] + (i<n-1?r[i+1]:0);
    
    while(low <= high)
    {
        if(l[low] == r[high]  && low!=high)
        {
            mx = max(mx, low + 1 + n - high);
            low++;
            high--;
        }

        else if(l[low] < r[high]) low++;
        else high--;
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