
#include <bits/stdc++.h>

using namespace std;
#define ff first
#define ss second
#define pb push_back

bool sortByVal(const pair<char, int> &a, 
               const pair<char, int> &b) 
{ 
    if(a.ss%2) return 0;
    else if(b.ss%2) return 1;
    else return a.ff<b.ff;
}

void pallindrom(string& s, int l, int r)
{
    map<char,int> mp;
    for(int i=l;i<=r; i++)
        if(mp.find(s[i]) == mp.end()) mp[s[i]] = 1;
        else mp[s[i]]++;
    
    vector<pair<char,int>> v;
    int sz = 0, odd=0;
    for(auto i:mp) { v.pb(make_pair(i.ff,i.ss)); if(i.ss%2) odd++;}
    sz = v.size();

    if(odd>1) return;

    sort(v.begin(),v.end(), sortByVal);

    if(odd)
    {
        int mid = (l+r)/2,i,j;
        for( i=0, j=0; i<(r-l)/2 && j<sz-1;j++)
        {
            while(v[j].ss)
            {
                s[l+i] = s[r-i] = v[j].ff;
                v[j].ss-=2;
                i++;
            }
        }

        while(v[j].ss > 1)
            {
                s[l+i] = s[r-i] = v[j].ff;
                v[j].ss-=2;
                i++;
            }
        s[l+i] = v[j].ff;
    }

    else
    {
        for(int i=0, j=0; i< (r-l)/2 + 1 && j<sz;j++)
        {
            while(v[j].ss)
            {
                s[l+i] = s[r-i] = v[j].ff;
                v[j].ss-=2;
                i++;
            }
        }
    }
}

int main() {
    int len, q, l,r;
    string s;
    cin>>len>>s>>q;
    for(int i=0; i<q; i++)
    {
        cin>>l>>r;
        l--;
        r--;
        pallindrom(s,l,r);

    }

    cout<<s;
    return 0;
}