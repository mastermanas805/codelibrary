// https://leetcode.com/problems/swim-in-rising-water/

#define key pair<int,int>
#define ff first
#define ss second
class Solution {
public:
    int n;
    vector<key> dir = {{0,-1}, {-1,0}, {0, 1}, {1,0}};
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();
        vector<vector<bool>> vis(n , vector<bool>(n, false));
        vis[0][0] = 1;
        return max(grid[0][0] ,bfs(grid, vis, {0,0}));
    }

    int bfs(vector<vector<int>>& grid, vector<vector<bool>> vis, key curr) {

        if(curr == key{n-1, n-1}) return grid[n-1][n-1];

        queue<key> q;
        for(auto i: dir) {
            key dst = {curr.ff + i.ff, curr.ss + i.ss};
            if(dst.ff < 0 || dst.ff >= n || dst.ss < 0 || dst.ss >= n || vis[dst.ff][dst.ss]) continue;
            q.push(dst);
            vis[dst.ff][dst.ss] = 1;
        }

        int mn = INT_MAX;
        while(!q.empty()) {
            key front = q.front();
            mn = min(mn, max( grid[front.ff][front.ss] , bfs(grid, vis, front) ) );
            q.pop();
        }

        return mn;
    }
};