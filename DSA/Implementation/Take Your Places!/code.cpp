#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int, int>

int32_t main()
{
    int t, n;
    cin >> t;
    while (t--)
    {
        cin>>n;
        int a[n];
        for(int i=0;i<n;i++) cin>>a[i];
        int c = 1;
        for(int i=0;i<n-1;i++) if(a[i]%2 == a[i+1]%2) c++;
        if(n == 1 || c == 0) cout<<0;
        else if(c == n) cout<<-1;
        else cout<<ceil((c+1)/2);
        cout<<endl;
    }
}