//src = https://codeforces.com/contest/1611/problem/A
#include<bits/stdc++.h>
using namespace std;
#define ll long long int

ll sol(string s)
{
    if(s.length() == 1 && (s[0]-'0')%2 == 0) return 0;

    else if(s.length() == 1 && (s[0]-'0')%2 != 0) return -1;

    if((s[s.length() - 1] - '0')%2 == 0) return 0;

    if((s[0]-'0')%2 == 0) return 1;

    bool f = 0;
    
    for(int i=1; i<s.length(); i++)
      if((s[i]-'0')%2 == 0) return 2;
    
    return -1;
}

int main()
{
    int t;
    string s;
    cin>>t;
    while(t--)
    {
        cin>>s;
        cout<<sol(s)<<endl;

    }
}