#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to implement Dijkstra's Algorithm
    vector<int> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int src) {
        // Distance array initialized to large value
        vector<int> dist(V, 1e9);

        // Min-heap storing {distance, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, 
                       greater<pair<int,int>>> pq;

        // Distance to source is 0
        dist[src] = 0;

        // Push source into heap
        pq.push({0, src});

        // Process nodes until heap is empty
        while (!pq.empty()) {
            // Extract node with minimum distance
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Skip if this distance is outdated
            if (d > dist[node]) continue;

            // Traverse all adjacent neighbors
            for (auto it : adj[node]) {
                int next = it.first;
                int wt = it.second;

                // Relaxation check
                if (dist[node] + wt < dist[next]) {
                    // Update distance
                    dist[next] = dist[node] + wt;

                    // Push updated distance into heap
                    pq.push({dist[next], next});
                }
            }
        }
        return dist;
    }
};

int main() {
    // Number of vertices
    int V = 5;

    // Adjacency list {neighbor, weight}
    vector<vector<pair<int,int>>> adj(V);

    // Example edges
    adj[0].push_back({1, 2});
    adj[0].push_back({2, 4});
    adj[1].push_back({2, 1});
    adj[1].push_back({3, 7});
    adj[2].push_back({4, 3});
    adj[3].push_back({4, 2});

    // Run algorithm
    Solution obj;
    vector<int> dist = obj.dijkstra(V, adj, 0);

    // Print shortest distances
    for (int i = 0; i < V; i++) {
        cout << "Distance from 0 to " << i << " = " << dist[i] << endl;
    }
}
