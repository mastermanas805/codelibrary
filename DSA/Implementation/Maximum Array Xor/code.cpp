//https://www.codechef.com/problems/MAXARXOR
#include<bits/stdc++.h>
using namespace std;
#define ll  long long int

int main()
{
    ll t,n,k,mx;
    cin>>t;
    
    while(t--)
    {
        cin>>n>>k;
        mx = pow(2,n);
        cout<<min(mx, 2*k)*(mx -1)<<endl;
    }
}