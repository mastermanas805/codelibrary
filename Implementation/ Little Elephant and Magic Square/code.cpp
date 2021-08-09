#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int32_t main()
{
    int a[3][3], s[3] = {0},x;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
          cin>>a[i][j], s[i]+=a[i][j];
    
    x = (s[0]+s[1]+s[2])/2;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
             a[i][j] == 0? cout<<x-s[i]:cout<<a[i][j], cout<<" ";
        cout<<endl;
    }
}