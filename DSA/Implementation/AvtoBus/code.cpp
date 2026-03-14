//https://codeforces.com/problemset/problem/1679/A

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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t, x, y, four, six;
    cin>>t;
    while(t--)
    {
        four = six = 0;
        cin>>x;
        if(x%2) { cout<<-1<<endl; continue; }
        y = x;

        if(y%4 == 0) four = y/4;
        else
        {
            while( y%6 != 0) y-=4;
            four = y/4;
        }


        y = x;
        if(y%6 == 0) six = y/6;
        else
        {
            while( y%4 != 0) y-=6;
            six = y/6;
        }

        if(four == 0) four = six;
        if(six == 0) six = four;
        cout<<six<<"\t"<<four<<endl;

    }
}