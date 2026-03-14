//src = https://codeforces.com/contest/1611/problem/B
#include<bits/stdc++.h>
using namespace std;
#define ll long long int

ll sol(ll x, ll y)
{
    ll mn = 0;
    //(2,2)
     mn = max(mn, min(x/2, y/2));
    
    //(3,1)
     mn = max(mn, min(x/3, y/1));

    //(1,3)
     mn = max(mn, min(x/1, y/3));
    return mn;
}

int main()
{
    ll t, x, y;
    cin>>t;
    while(t--)
    {
        cin>>x>>y;
        cout<<sol(x,y)<<endl;

    }
}