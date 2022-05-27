#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


int solve(string &s)
{
    cin>>s;
    int result = 0, n = s.length();
    bool a[n+1], b[n+1];
    a[0] = b[0] = true;

    for(int i = 0; i<n; i++)
        a[i + 1] = a[i] && (s[i] == '1' || s[i] == '?');
    
    for (int i = n - 1; i >= 0; i--)
            b[n - i] = b[n - i - 1] && (s[i] == '0' || s[i] == '?');
    
    for(int i=0; i<n; i++)
       if (a[i] && b[n - i - 1])
            result++;
    
    return result;
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    string s;
    
    cin>>t;
    while(t--)
        cout<<solve(s)<<endl;

}