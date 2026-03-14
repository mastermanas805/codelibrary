#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{
    ll t,n,x,sum; 
    cin>>t;
    while(t--)
    {
        sum=0;
        cin>>n;
        for(int i=0; i<n;i++)
         {
             cin>>x;
             sum+=x;
         }

        cout<<(n - sum%n)*(sum%n)<<endl;
    }
}