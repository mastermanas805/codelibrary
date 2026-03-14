class Solution {
public:
    vector<pair<int, int>> neighbours = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int levels = -1;
        queue<pair<int, int>> q;
        bool isEmpty = true;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                isEmpty = isEmpty && !(grid[i][j] == 1 || grid[i][j] == 2);
                if (grid[i][j] == 2)
                    q.push({i, j});
            }
        
        if(isEmpty) return 0;

        while (!q.empty()) {
            levels++;
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                pair<int, int> coordinates = q.front();
                q.pop();

                for (auto i : neighbours) {
                    int x = coordinates.first + i.first;
                    int y = coordinates.second + i.second;
                    if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {
                        grid[x][y] = 2;
                        q.push({x, y});
                    }
                }
            }
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                    return -1;

        return levels;
    }
};