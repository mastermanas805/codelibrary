#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> graph;
    vector<int> count, res;
    int N;

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        this->N = N;
        this->res = vector<int>(N, 0);
        this->count = vector<int>(N, 0);
        this->graph = vector<vector<int>>(N);

        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        dfs1(0, -1);
        dfs2(0, -1);
        return res;
    }

    void dfs1(int cur, int parent) {
        count[cur] = 1;
        for (int child : graph[cur]) {
            if (child != parent) {
                dfs1(child, cur);
                count[cur] += count[child];
                res[cur] += res[child] + count[child];
            }
        }
    }

    void dfs2(int cur, int parent) {
        for (int child : graph[cur]) {
            if (child != parent) {
                res[child] = res[cur] + N - 2 * count[child];
                dfs2(child, cur);
            }
        }
    }
};