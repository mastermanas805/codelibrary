#include<bits/stdc++.h>
using namespace std;

int solve(long &n)
{
    long temp = n;
    int x,y,cnt;
    x = y = INT_MAX; cnt = 0;
    while(n)
    {
        if(n%10 < x) y = x, x = n%10;
        else if(n%10 < y) y = n%10;
        cnt++;
        n/=10;
    }

    if(cnt == 2 ) return temp%10;
    return x;
}
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;
    long n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<solve(n)<<endl;
    }
}