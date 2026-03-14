#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second

vector<pair<pair<int,int>, pair<int,int>>> p = { make_pair(make_pair(0,0), make_pair(2,2)), 
                                                 make_pair(make_pair(0,1), make_pair(2,1)),
                                                 make_pair(make_pair(0,2), make_pair(2,0)),
                                                 make_pair(make_pair(1,0), make_pair(1,2)) };

int square(int a[3][3])
{

    int count = 0, x;
    if(a[0][0] - a[0][1] == a[0][1]-a[0][2])
       count++;
    
    if(a[0][0] - a[1][0] == a[1][0] - a[2][0])
       count++;
    
    if(a[0][2] - a[1][2] == a[1][2] - a[2][2])
       count++;
    
    if(a[2][0] - a[2][1] == a[2][1] - a[2][2])
       count++;
    
    map<int,int> mp;

    for(auto i = p.begin(); i!=p.end(); i++)
    {
        x = abs(a[i->f.f][i->f.s] - a[i->s.f][i->s.s]);
        if(x%2 == 0)
        {
            x/=2;
            x = min(a[i->f.f][i->f.s] ,a[i->s.f][i->s.s]) + x;
            if(mp.find(x) == mp.end())
                mp[x] = 1;
            else
                mp[x]++;
        }
    }
    
    int y = 0;
    
    for(auto i = mp.begin(); i!=mp.end(); i++)
       y = max(y,i->s);
        
    return count+y;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a[3][3];
        cin>>a[0][0]>>a[0][1]>>a[0][2]>>a[1][0]>>a[1][2]>>a[2][0]>>a[2][1]>>a[2][2];
        cout<<square(a)<<endl;
    }
}