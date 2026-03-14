#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

vector<int> sol(int q)
{
    vector<int> ret;
    unordered_map<int,int> mp;
    unordered_map<int,stack<int>> st;
    priority_queue<int> pq;
    
    int x,n, temp, num;
    for(int i=0;i<q;i++)
    {
        cin>>x>>n;
        switch(x){
            case 1:
                mp[n]++;
                st[mp[n]].push(n);
                pq.push(mp[n]);
                break;
            case 2:
                // Get largest frequency
                temp = pq.top();
                pq.pop();
                //Get latest element with freq
                num = st[temp].top();
                //remove the element from top of the given freq
                st[temp].pop();
                //decrease the freq of num
                mp[num]--;
                //record the num
                ret.push_back(num);
                break;
            default: break;
        }
    }
    return ret;
}

int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<int> res = sol(n);

        for(auto i: res){
            cout<<i<<"\t";
        }

        cout<<"\n";
    }
}