// https://leetcode.com/problems/cheapest-flights-within-k-stops/

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int,int>> adj[n];
        for(auto i: flights){
            adj[i[0]].push_back({i[1], i[2]});
        }
        
        vector<int> stops(n, INT_MAX);
        priority_queue< vector<int> ,vector<vector<int>>, greater<vector<int>> > pq;
        pq.push({0,src,0});
        
        while(pq.size() > 0){
            int cost = pq.top()[0], v = pq.top()[1], curr_stops = pq.top()[2];
            pq.pop();
            if(v == dst) return cost;
            if(stops[v] < curr_stops || curr_stops > k) continue;
            stops[v] = curr_stops;
            
            for(auto i: adj[v])
                pq.push({cost+i.second, i.first, curr_stops+1});

        }
        
        return -1;
    }
};