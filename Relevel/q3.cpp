#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>

class Solution {
public:
    int longestSubsequence(int arr[], int n,  int diff) {
        int res = 1;
        unordered_map<int,int> maxmap;
        for(int i = 0 ; i < n ; i++)
            maxmap[arr[i]] = maxmap[arr[i]-diff]+1;

            
        for(auto it : maxmap)
        {
            int x = 0;
            for(int i=0; i<=diff; i++)
                    if(maxmap.count(it.ff - i))
                        x+ = maxmap[it.ss - i];
            res = max(res,x);
        }
            
        return res;
    }
};

int main()
{
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++)
          cin>>a[i];
        Solution s;
        cout<<s.longestSubsequence(a,n,2)<<endl;
    }
}