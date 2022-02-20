//https://codeforces.com/contest/1611/problem/C
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define mx 10

void sol(list<int> a, ll n)
{
    list <int> l;
    int x;
    ll num = 0;

    while(!a.empty())
    {

    }

    while(!l.empty())
    {
        cout<<*l.begin()<<" ";
    }
}

int main()
{
    ll t, n,x;
    list <int> l;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(ll i=0; i<n;i++)
           cin>>x, l.push_back(x);
        
        sol(l,n);

    }
}