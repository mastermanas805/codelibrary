#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }


string s1,s2;
int a[26];
int i,j,n1,n2;
bool f,g,h;

void sol()
{
        cin>>s1>>s2;
        memset(a,0,sizeof(a));
        n1=s1.length(),n2=s2.length();
        f = g = h = 1;

        for(i=0,j=0;i<n1;i++)
        {
         if(j<n2 && s1[i] == s2[j]) j++;
         if(j == n2) f = 0; 
        }
        
        for(i=0;i<n1;i++) a[s1[i]-'a']++;
        for(i=0;i<n2;i++) a[s2[i]-'a']--;
        
        for(i=0;i<26;i++) {if(a[i]<0) { cout<<"need tree"<<endl; return;} g&=a[i]==0, h&=a[i]>=0;}

        if(!f) cout<<"automaton";
        else if(g) cout<<"array";
        else if(h) cout<<"both";
        else cout<<"need tree";
        cout<<endl;
        return;
}

int main()
{
    int t;
    bool f;
    sol();
}