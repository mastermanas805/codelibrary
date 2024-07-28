#define mx 100001
class Solution {
public:
    int dis[101][101];

    Solution() { memset(dis, INT_MAX, sizeof(dis)); }

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1; // If start or end is blocked, return -1
        }

        vector<vector<int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                          {0, 1},   {1, -1}, {1, 0},  {1, 1}};
        queue<tuple<int, int, int>> q; // (x, y, distance)
        q.push({0, 0, 1});
        grid[0][0] = 1; // Mark as visited

        while (!q.empty()) {
            auto [x, y, dist] = q.front();
            q.pop();

            if (x == n - 1 && y == n - 1) {
                return dist;
            }

            for (const auto& dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];

                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    grid[nx][ny] == 0) {
                    q.push({nx, ny, dist + 1});
                    grid[nx][ny] = 1; // Mark as visited
                }
            }
        }

        return -1;
    }
};