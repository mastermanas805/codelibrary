//https://codeforces.com/contest/1550/problem/A
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t,s,ans,sum,inc;
    cin>>t;
    while(t--)
    {
        cin>>s;
        ans = 0;
        sum = 0;
        inc = 1;
        while(sum < s)
        {
            sum += inc;
            inc+=2;
            ans++;
        }

        cout<<ans<<endl;

    }
}