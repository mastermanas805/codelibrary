#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int main()
{
    int t,n,i;
    long double m,sum,c;
    cin>>t;
    while(t--)
    {
        m = INT_MIN;
        sum = 0;
        cin>>n;
        long double x;
        for(c=0, i=0; i<n; i++,c++) 
        {  
            scanf("%Lf",&x);
            m = max(m,x);
            sum+=x;
        }

        sum-=m;
        sum = m+sum/(c-1);
        cout<<setprecision(11)<<sum<<endl;     
    }
}