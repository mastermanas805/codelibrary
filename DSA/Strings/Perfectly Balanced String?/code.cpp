#include<bits/stdc++.h>
using namespace std;
#define int long long


bool solve(string& s)
{
    int i = 0, j,n = s.length();
    set<char> unique;
    for(i = 0; i<n; i++)
      if(unique.find(s[i]) == unique.end()) unique.insert(s[i]);
      else break;
    
    for(int j=i; j<n; j++)
        if(s[j] != s[j-i]) return 0;
    
    return 1;
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    string s;
    bool f;
    cin>>t;
    while(t--)
    {
        cin>>s;
        f = solve(s);

        cout<<(f?"yes":"no")<<endl;
    }
}