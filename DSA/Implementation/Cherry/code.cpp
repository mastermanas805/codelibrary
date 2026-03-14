#include<bits/stdc++.h>
using namespace std;
#define int long long

int32_t main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int a[n];

        int  x = 1,y;
        for(int i=0;i<n;i++)  cin>>a[i];

        sort(a,a+n);
        int mx = a[n-1];
        int mn = a[n-2];
        for(int i=n-2;i>=0;i--)
         {
             if(a[i] != mx)
               {
                   mn = a[i];
                   break;
               }
         }
        cout<<mx*mn<<endl;
    }
}
