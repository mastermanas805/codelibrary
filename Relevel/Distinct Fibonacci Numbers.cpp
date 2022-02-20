#include <bits/stdc++.h>
#define mx 1000000007
#define ll long long
using namespace std;

int main()
{
    int n,x,y;
    cin>>n;
    
    for(int i=0; i<n; i++)
      {
          cin>>x>>y;
          if(y%x == 0)
              cout<<y/x<<endl;
          else
            cout<<max(x,y)<<endl;
      }
    

    return 0;
}