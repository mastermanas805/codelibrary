// { Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
// User function Template for C++

#define ll unsigned long long
class Solution {
  public:
    ll minimumCost(int n, int m, int x, vector<int> &a,
                          vector<vector<int>> &b) {
        ll int cost = a[0]; 
        cost+= a[n-1];
        cost+= x;
        bool visited[n+1] = {0};
        
        set<pair<ll,int>> st;
        vector<int> adj[n+1];
        
        for(auto it: b){
            adj[it[0]-1].push_back(it[1]-1);
            adj[it[1]-1].push_back(it[0]-1);
        }
        
        st.insert({0,0});
        ll dist[n];
        for(int i=0;i<n; i++) dist[i] = 1e18;
        
        dist[0] = 0;
        
        while(!st.empty()){
            auto x =  *st.begin();
            ll dis = x.first;
            int node = x.second;
            st.erase({dis, node});
            
            if(visited[node] == 1) continue;
            
            visited[node] = 1;
            for(auto it: adj[node]){
                if(!visited[it] && dis + a[node] + a[it] < dist[it]){
                    dist[it] = dis + a[node] + a[it];
                    st.insert({it, dist[it]});
                }
            }
        }
        
        cost = min(cost, dist[n-1]);
        return cost;
    }
};




// { Driver Code Starts.

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        int n, m, x;
        cin >> n >> m >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<vector<int>> b(m, vector<int>(2, 0));
        for (int i = 0; i < m; i++) cin >> b[i][0] >> b[i][1];
        Solution obj;
        long long ans = obj.minimumCost(n, m, x, a, b);
        cout << ans << endl;
    }

    return 0;
}
  // } Driver Code Ends