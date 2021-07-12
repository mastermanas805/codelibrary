#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t, x, y, x1, y1, x2,y2;
    cin>>t;

    while(t--)
    {
        cin>>x>>y>>x1>>y1>>x2>>y2;
        int dis = abs(x-x1)+abs(y-y1);
        if((x == x1 && x == x2) && ((y< y2) && (y2< y1) || (y> y2) && (y2> y1) ))
          cout<<dis+2;
        
        else if((y == y1 && y == y2) && ((x< x2) && (x2< x1) || (x> x2) && (x2> x1) ) )
          cout<<dis+2;
        
        else
          cout<<dis;
        
        cout<<endl;
    }
}