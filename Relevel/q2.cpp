#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>

int gcd(int a, int b)
{
    if(b == 0)  return a;

    return gcd(b, a%b);
}
int main()
{
    int n,q,t,a,s,i,l,r,x,y,z;
    cin>>n>>q;
    vector<vector<pii>> v(n);
    while(q--)
    {
        cin>>t;
        if(t == 1)
         {
             cin>>a>>s>>i;
             i--;
             v[i].pb(mp(a*s,s));
         }
        
        else
        {
            cin>>l>>r;
            l--, r--;
            x = y = 0;
            for(int j =l; j<=r; j++)
              for(int k =0; k<v[j].size(); k++)
                 x+=v[j][k].ff, y+=v[j][k].ss;
            
            z = gcd(x,y);
            if(z == 1 || z == 0)
              cout<<x<<" "<<y;
            else
             cout<<z;
        }
    }
}