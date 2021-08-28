#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }
#define mx 10000
bool prime[mx+1];

void SieveOfEratosthenes()
{
    
    memset(prime, true, sizeof(prime));
    prime[1] = 0;

    for (int p = 2; p * p <= mx+1; p++)
    {
        // If prime[p] is not changed,
        // then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples
            // of p greater than or
            // equal to the square of it
            // numbers which are multiple
            // of p and are less than p^2
            // are already been marked.
            for (int i = p * p; i <= mx+1; i += p)
                prime[i] = false;
        }
    }
}


void compute()
{
    int s;
    string no;
    cin>>s>>no;
    vector<int> n(s);
    for(int i=0;i<s;i++) n[i]=no[i]-'0';

    for(int i=0; i<s;i++) if(!prime[n[i]]) {cout<<1<<endl<<n[i]; return;}

    for(int i=0;i<s;i++)
    {
        int x = n[i];

        for(int j=i+1;j<s;j++)
        {
            if(i!=j && !prime[x*10 + n[j]]) {cout<<2<<endl<<x*10 + n[j]; return;}
        }
    }


    for(int i=0;i<s;i++)
    {
        int x = n[i];

        for(int j=i+1;j<s;j++)
        {
            int y = x*10 + n[j];
            for(int k=j+1;k<s;k++) if(!prime[y*10 + n[k]]) 
              {cout<<3<<endl<<y*10 + n[k]; return;}
        }
    }

    for(int i=0;i<s;i++)
    {
        int x = n[i];

        for(int j=i+1;j<s;j++)
        {
            int y = x*10 + n[j];
            for(int k=j+1;k<s;k++) 
            {
                int z = y*10 + n[k];
                for(int m=k+1;m<s;m++)
                if(!prime[z*10 + n[m]]) 
              {cout<<3<<endl<<y*10 + n[m]; return;}
            }
            
        }
    }


}

int32_t main()
{
    SieveOfEratosthenes();
    int t,s;
    cin>>t;
    
    while(t--)
    {
        compute();
        cout<<endl;
    }
}