//  https://leetcode.com/problems/course-schedule/

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
};