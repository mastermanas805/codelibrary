#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int32_t main()
{
    int t,n,k,x,i,j,s;
    bool flag;
    cin>>t;
    while(t--)
    {
        flag = 1;
        cin>>n>>k;
        int a[n];
        for(i=0;i<n;i++) cin>>a[i];

        vector<pii> v;
        v.reserve(n);
       
        for(i=0;i<n;i++)
        {
            j = i;
            while(a[i] < a[++i] && i<n);
            i--;
            v.pb(mp(a[j],a[i]));
        }

        sort(v.begin(),v.end());
        s = v.size();
        for(i=0; i<s; i++)
        {
            j = i;
            while(v[j].ss >v[++i].ff && v[i].ff <= v[f].ff && i<s)
            {
                cout<<"NO"<<endl;;
                flag = 0;
                break;
            }
            if(!flag) break;
            i--;
        }
        if(flag == 1) if(s<=k) cout<<"YES"<<endl; else cout<<"NO"<<endl;
    }
}