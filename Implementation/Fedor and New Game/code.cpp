//https://codeforces.com/problemset/problem/467/B
#include<bits/stdc++.h>
using namespace std;
#define ll long long int

bool calc(ll n, ll k)
{
    int count=0;
    while (n!=0)
    {
        n = n & (n-1);
        count++;
    }

    return count<=k?1:0;
}

int main()
{
    ll n,m,k,count;
    cin>>n>>m>>k;
    
    vector<int> a(m+1);
    for(int i=0;i<m+1;i++) cin>>a[i];
    
    count=0;
    
    for(int i=0;i <m;i++)
        count+=calc(a[i]^a[m], k);
        
    cout<<count<<endl;
    
}