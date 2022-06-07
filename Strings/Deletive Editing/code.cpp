#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


bool solve(string& a, string& b)
{
    int x[26], y[26], m = a.length(), n = b.length(), i, j;
    string temp;
    memset(x,0,sizeof(x));
    memset(y,0, sizeof(y));

    for(auto o: a) x[o-'A']++;
    
    for(auto o: b) y[o-'A']++;

    for(i = 0; i<26; i++) if(x[i] - y[i] < 0) return 0;

    for(i=0;i<m; i++)
        if(x[a[i]-'A'] - y[a[i]-'A'] > 0) x[a[i]-'A']--;
        else temp+=a[i];

    for(i=temp.length(), j = n-1; i>=0 && j>=0; i--)
        if(temp[i] == b[j]) j--;
    
    if(j >= 0) return 0;

    return 1;
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
        cout<<( solve(a,b)?"yes":"no" )<<endl;
    }

}