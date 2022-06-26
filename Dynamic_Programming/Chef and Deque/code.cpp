#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }
unordered_set<int> f;

int sol()
{
    int n,k,ans = 0,i=0;
    cin>>n>>k;
    int a[n], b[n];
    for(int i=0; i<n; i++) {cin>>a[i]; if(!i) b[i] = a[i]; else b[i]= b[i-1] + a[i];}
    int l=0, r=n-1;
    
    if(a[n-1]%k == 0) return 0;

    while((1<<i) <= n)
    {
        if(f.find(i) == f.end())
        {
            if(b[n-1-(1<<i)]%k == 0) {f.insert(i); return 1;}
            else
            {
                j =0;
                if(f.find(j) == f.end())
            }
            else if( (b[n-1-(1<<i)] - b[(1<<i) - 1])%k ==0 ) {f.insert(i); return i;}
        }
        i++;
    }

    return -1;
}

int32_t main()
{
    int t,n;
    cin>>t;
    while(t--)  cout<<sol()<<endl;

}