#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


bool solve(int a[], int n)
{   
    return a[n-1] - a[0] - n + 1 <= 2? 1: 0;

}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];

        cout<<(solve(a,n)?"yes":"no")<<endl;
    }
}