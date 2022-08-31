// https://leetcode.com/problems/network-delay-time/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        
        vector<pair<int, int>> adj[n+1];
        for(auto i: times){
            
            int x = i[0];
            int y = i[1];
            int z = i[2];
            pair<int, int> pr = {i[1], i[2]};
            adj[x].push_back(pr);
            
        }
        
        vector<int> dis(n+1, INT_MAX);
        dis[k] = 0;
        queue<int> q;
        q.push(k);
        
        while(!q.empty()){
            
            int node = q.front();
            q.pop();
            
            for(auto i: adj[node]){
                
                if(dis[i.first] > i.second + dis[node]){
                    dis[i.first] = i.second + dis[node];
                    q.push(i.first);
                }
            }
        }
        int ans = *max_element(dis.begin()+1, dis.end());
        if(ans == INT_MAX) return -1;
        return ans;
    }
};
