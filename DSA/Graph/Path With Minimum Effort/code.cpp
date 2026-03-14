class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = n > 0 ? heights[0].size() : 0;

        if (n * m == 0)
            return 0;

        int effortMatrix[n + 1][m + 1];
        memset(effortMatrix, 1000000, sizeof(effortMatrix));

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                       greater<tuple<int, int, int>>> q;

        vector<vector<int>> neighbours = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        q.push({0, 0, 0});
        effortMatrix[0][0] = 0;

        while (!q.empty()) {
            auto [currEffort, x, y] = q.top();
            q.pop();

            if (x == n - 1 && y == m - 1) {
                return currEffort;
            }

            for (vector<int> i : neighbours) {
                int dx = x + i[0], dy = y + i[1];

                if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                    int effort =
                        max(abs(heights[dx][dy] - heights[x][y]), currEffort);
                    if (effort < effortMatrix[dx][dy]) {
                        effortMatrix[dx][dy] = effort;
                        q.push({effort, dx, dy});
                    }
                }
            }
        }

        return 0;
    }
};