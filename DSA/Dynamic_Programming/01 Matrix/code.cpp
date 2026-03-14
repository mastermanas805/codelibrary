// https://leetcode.com/problems/01-matrix/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        vector<vector<int>> ret(n, vector<int>(m, -1));
        queue<pair<pair<int,int>, int>> q;

        // Initialize the queue with the positions of '0' cells and mark them as visited.
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(mat[i][j] == 0) {
                    q.push({{i, j}, 0}); // Position (i, j) and distance 0.
                    visited[i][j] = true;
                }
                else {
                    visited[i][j] = false; // Mark non-'0' cells as unvisited.
                }
            }
        }

        while(!q.empty()) {
            pair<pair<int,int>, int> x = q.front();
            q.pop();
            ret[x.first.first][x.first.second] = x.second;

            pair<int, int> arr[] = {
                {x.first.first + 1, x.first.second},
                {x.first.first - 1, x.first.second},
                {x.first.first, x.first.second + 1},
                {x.first.first, x.first.second - 1}
            };

            for(pair<int, int> i : arr) {
                if(i.first < 0 || i.second < 0 || i.first >= n || i.second >= m)
                    continue;
                if(visited[i.first][i.second])
                    continue;
                visited[i.first][i.second] = true;
                q.push({i, x.second + 1}); // Increment the distance and add to the queue.
            }
        }

        return ret;
    }
};

int main() {
    // Example usage and testing of the Solution class and updateMatrix function
    return 0;
}
