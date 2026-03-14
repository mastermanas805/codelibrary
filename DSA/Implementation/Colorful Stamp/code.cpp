#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


enum color { red, blue, white };

bool check(string s, int n)
{
    if(n == 0) return 1;
    
    int a[2] = {0,0};

    for(auto i:s)
        switch (i)
       {
            case 'R':
                a[red]++;
                break;
            case 'B':
                a[blue]++;
                break;
            default:
                break;
       }
    
    if(a[red] == 0 || a[blue] == 0) return 0;
    return 1;
}

bool solve(string &s, int &n)
{
    string val;
    stringstream streamData(s);
    while (getline(streamData, val, 'W')) 
        if(!check(val, val.length())) return 0;

    return 1;
}


int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t,n;
    string s;
    cin>>t;
    while(t--)
    {
        cin>>n>>s;

        cout<<( solve(s,n)? "yes": "no" )<<endl;
    }
}