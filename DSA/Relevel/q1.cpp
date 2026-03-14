#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<ll,ll>


bool comp(pii a, pii b)
{
    if(a.ff == b.ff)
       return a.ss < b.ss;
    return a.ff < b.ff;
}

bool sol(vector<pii>& v)
{
    pii x, y;
    x = v[0];
    if(v.size() >1)
        y = v[1];

    for(int i=2; i<v.size(); i++)
    {
        if(v[i].ff > x.ss)
           x = v[i];
        else if(v[i].ff > y.ss)
          y = v[i];
        else return 0;
    }
    return 1;
}

int main()
{
    int t;
    ll n,x,y;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<pii> v;
        for(ll i=0; i<n; i++)
        {
            cin>>x>>y;
            v.pb(mp(x,y));
        }

        sort(v.begin(), v.end(), comp);
        if(sol(v)) cout<<"YES";
        else cout<<"NO";
        cout<<endl;
    } 
}