#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    void dfs(vector<vector<int>> * adj, int node, int par, vector<int> & cost) {
        for(auto &kid: adj[node]) {
            int dir = kid[1];
            int v = kid[0];
            if(v != par) {
                dfs(adj, v, node, cost);
                cost[node] += dir + cost[v];
            }
        }
    }
    
    void reroot(vector<vector<int>> * adj, int node, int par, vector<int> & cost) {
        for(auto & kid: adj[node]) {
            int dir = kid[1] ^ 1;
            int v = kid[0];
            
            if(v != par) {
                // calculate for v considering cost of node in mind.
                cost[v] += (cost[node] - cost[v] - (dir ^ 1)) + dir;
                reroot(adj, v, node, cost);
            }
        }
    }
    
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        
        vector<vector<int>> adj[n];
        vector<int> cost(n);
        for(auto it: edges) {
            adj[it[0]].push_back({it[1], 0});
            adj[it[1]].push_back({it[0], 1});
        }
        
        dfs(adj, 0, -1, cost);
        reroot(adj, 0, -1, cost);
        return cost;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> adj = {{2,0},{2,1},{1,3}};
    Solution s;
    s.minEdgeReversals(n, adj);
}