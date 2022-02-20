#include <bits/stdc++.h>
#define mx 1000000007
#define ll long long
using namespace std;

int main()
{
    int n;
    cin>>n;
    ll a[n], sum = 0, res = 0, x;
    
    for(int i=0; i<n; i++)
      {
          cin>>a[i];
          sum = (sum + a[i]%mx)%mx;
      }
    
    for(int i=0; i<n; i++)
    {
        x = (a[i]%mx * (sum - a[i])%mx)%mx;
        res = (x + res)%mx;
    }
    
    cout<<res<<endl;
    

    return 0;
}

