#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;
        vector<vector<pair<int, int>>> graph(n);
        vector<long long> cost(n, LLONG_MAX);  // Use long long for large numbers
        vector<long long> ways(n, 0);  // Use long long for large numbers
        
        // Build the graph
        for (vector<int>& road : roads) {
            graph[road[0]].emplace_back(road[1], road[2]);
            graph[road[1]].emplace_back(road[0], road[2]);
        }
        
        // Priority queue for Dijkstra's algorithm
        priority_queue<tuple<long long, int>, vector<tuple<long long, int>>, greater<>> pq; // (cost, node)
        
        pq.emplace(0, 0);  // Start from node 0 with cost 0
        cost[0] = 0;
        ways[0] = 1;
        
        while (!pq.empty()) {
            auto [dis, node] = pq.top();
            pq.pop();
            
            if (dis > cost[node]) continue;  // Skip if current distance is not optimal
            
            for (const auto& [nextNode, nextCost] : graph[node]) {
                long long newCost = dis + nextCost;
                
                if (newCost < cost[nextNode]) {
                    cost[nextNode] = newCost;
                    ways[nextNode] = ways[node];
                    pq.emplace(newCost, nextNode);
                } else if (newCost == cost[nextNode]) {
                    ways[nextNode] = (ways[nextNode] + ways[node]) % MOD;
                }
            }
        }
        
        return ways[n-1];
    }
};