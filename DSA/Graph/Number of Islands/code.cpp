// https://leetcode.com/problems/number-of-islands/
class Solution {
public:
    bool solve(vector<vector<char>>& g, vector<vector<bool>>& visited, int& m, int& n, int i, int j){

        if(i>=m || j>=n || i<0 || j<0) return 0;
        if(g[i][j] == '0' || visited[i][j] == true) return false;
        visited[i][j] = true;
        bool f = true;
        f |= solve(g, visited,m,n, i - 1, j);
        f |= solve(g,visited,m,n, i, j + 1);
        f |= solve(g,visited,m,n, i + 1, j);
        f |= solve(g,visited,m,n, i , j - 1);
        return f;
    }


    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n,false));
        bool f;
        int cnt = 0;

        for(int i=0; i<m; i++){
            for(int j=0;j<n;j++){
                f = solve(grid, visited, m,n,i,j);
                if(f) cnt++;
            }
        }
        return cnt;
    }
};