//https://codeforces.com/problemset/problem/454/B
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{
    ll n, st = 0;
    bool f;
    cin>>n;
    ll a[n], b[n];
    
    for(ll i=0; i<n; i++) 
    {
      cin>>a[i];
      b[i] = a[i];
      if(a[st] >= a[i])
        st = i;
    }
    
    sort(b, b + n);
    f = 1;
    for(ll i=0; i< n; i++)
      if(b[i] != a[(i+st)%n])
        {
            cout<<-1;
            f = 0;
            break;
        }
    
    if(f && st == 0)
       cout<<0;
    else if(f)
      cout<<n-st;
    
    cout<<endl;
}