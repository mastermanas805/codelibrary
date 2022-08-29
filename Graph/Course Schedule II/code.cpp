// https://leetcode.com/problems/course-schedule-ii/

class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& edges) {
        bool visited[n];
        int x;
        vector<int> adj[n];
        memset(visited, false, sizeof(visited));
        queue<int> q;
        int cnt[n];
        memset(cnt, 0, sizeof(cnt));
        for(auto i: edges){
            cnt[i[0]]++;
            adj[i[1]].push_back(i[0]);
        }
        
        for(int i=0;i<n; i++)
            if(cnt[i] == 0)
                q.push(i);
        
        while(!q.empty()){
            x = q.front();
            q.pop();
            if(cnt[x] == 0){
                for(auto i: adj[x]){
                    cnt[i]--;
                    if(cnt[i] == 0) q.push(i);
                }
            }
        }
        
        for(auto i: cnt)
            if(i > 0) return 0;
        
        return true;
        
    }
    
    void topologicalsort(vector<bool>& visited, vector<int> adj[], stack<int>& s, int node){
        visited[node] = true;
        for(auto i: adj[node])
            if(!visited[i])
                topologicalsort(visited, adj, s,i);
        
        s.push(node);
    }
    
    vector<int> findOrder(int n, vector<vector<int>>& edges) {
        if(!canFinish(n,edges)) return {};
        vector<int> adj[n];
        stack<int> s;
        for(auto i: edges) adj[i[1]].push_back(i[0]);
        vector<bool> visited(n,0);
        
        for(int i=0;i<n;i++)
            if(!visited[i])
                topologicalsort(visited, adj, s,i);
        
        vector<int> ret;
        while(!s.empty()){
            ret.push_back(s.top());
            s.pop();
        }
        
        return ret;
            
    }
};