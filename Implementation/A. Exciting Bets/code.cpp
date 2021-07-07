#include <bits/stdc++.h>
using namespace std;
#define ll long double

pair<ll,ll> bets(ll a, ll b)
{
    if(a == 0 && b ==0)
       return make_pair(0,0);
    ll dif = abs(a-b);
    if(dif == 0)
      return make_pair(0,0);
    ll y =min(a - floor(a/dif)*dif , ceil(a/dif)*dif - a) ;
    return make_pair(  dif,  y);

}

int main()
{
    ll t,a,b;
    cin>>t;
    while(t--)
     {
         cin>>a>>b;
         pair<ll , ll> p = bets(a,b);
         cout<<p.first<<" "<<p.second<<endl;
     }
}