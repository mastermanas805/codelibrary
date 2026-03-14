#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>

int sol(int a[], int n, int k)
{
    if(n == 1) return max(a[0], a[0] + k -1);

    int b[n], c[n];
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));

    int st = -1, i=0;
    // left to right
    while(a[i] == 0 && i<n) i++;
    st = i;
    if(st >= n) return 0;

    i++;
    while(i<n)
    {
        if(a[i-1] > 0) b[i] = 1;
        
        else b[i] = b[i-1] + 1;
        i++;
    }

    if(a[n-1] > 0) b[0] = 1;
    else b[0] = b[n-1] + 1;
    
    i = 1;
    while(i <= st)
    {
        if(a[i-1] > 0) b[i] = 1;
        
        else b[i] = b[i-1] + 1;
        i++;
    }
    
    for(int i=0; i<n; i++) if(b[i] == 0) b[i]=b[i-1]+1;


    //right to left
    st = -1, i = n-1;

    while(i>=0 && a[i] == 0) i--;
    st = i;
    i--;
    while(i>=0)
    {
        if(a[i+1] > 0) c[i] = 1;
        
        else c[i] = c[i+1] + 1;
        i--;
    }
    
    if(a[0] > 0) c[n-1]= 1;
    else c[n-1] = c[0] + 1;

    i = n-2;

    while(i >= st)
    {
        if(a[i+1] > 0) c[i] = 1;
        
        else c[i] = c[i+1] + 1;
        i--;
    }

    for(int i=n-2; i>=0; i--) if(c[i] == 0) c[i]=c[i+1]+1;

    //merge 
    for(int i=0; i<n; i++) b[i] = min(b[i],c[i]);
    
    int count = 0, x;
    for(int i=0; i<n; i++)
    {
        x = a[i];
        
        if(i == 0)
        {
            if(a[n-1] > 0) x+=k;
            else if(k > b[n-1]) x+=(k-b[n-1]);

            if(a[1] >0) x+=k;
            else if(k > b[1]) x+=(k-b[1]);
        }

        else if(i == n-1)
        {
            if(a[0] >0) x+=k;
            else if(k > b[0]) x+=(k - b[0]);

            if(n>2 && a[n-2]>0) x+=k;
            else if(n>2 && k > b[n-2]) x+=(k - b[n-2]);
        }

        else
        {
            if(a[i-1]>0) x+=k;
            else if(k > b[i-1]) x+= (k - a[i-1]);

            if(a[i+1]>0) x+=k;
            else if(k > b[i+1]) x+= (k - a[i+1]);
        }
        count+= max(a[i], x);
    }

    return count;
}


int32_t main()
{
    int t,n,k;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        int a[n];
        for(int i=0; i<n; i++) cin>>a[i];
        cout<<sol(a,n,k);
    }
}