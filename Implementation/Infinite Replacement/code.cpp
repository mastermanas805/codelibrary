#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


int solve(string &a, string &b)
{
    if(b == "a") return 1;

    for(auto i: b)
        if(i == 'a') return -1;

    return pow(2,a.length());
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    string a,b;

    cin>>t;
    while(t--)
    {
        cin>>a>>b;

        cout<<solve(a,b)<<endl;
    }
}