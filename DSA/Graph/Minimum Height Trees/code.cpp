// https://leetcode.com/problems/minimum-height-trees/

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if( n <=1) return {0};
        vector<int> adj[n];
        int d[n],x,sz;
        memset(d, 0, sizeof(d));
        
        for(auto i: edges){
            d[i[0]]++;
            d[i[1]]++;
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }
        
        queue<int> q;
        for(int i=0;i<n;i++)
            if(d[i] == 1) q.push(i);
        
        while(n>2){
            sz = q.size();
            n-=sz;
            while(sz--){
                x = q.front();
                q.pop();
                for(auto i: adj[x]){
                    d[i]--;
                    if(d[i] == 1) q.push(i);
                }
            }
        }
        
        vector<int> ret;
        while(!q.empty()){
            ret.push_back(q.front());
            q.pop();
        }
        
        return ret;
    }
};