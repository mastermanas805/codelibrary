// https://leetcode.com/problems/sum-of-distances-in-tree/
#define mx 30001

class Solution {
public:
    vector<vector<int>> *dp, *graph;
    vector<bool> *vis;

    int dfs(int i, int j) {
        if(i == j) return 0;
        if ((*dp)[i][j] < mx) return (*dp)[i][j];
        
        for (auto node : (*graph)[i]) {
            if (!(*vis)[node]) {
                (*vis)[node] = true;
                (*dp)[i][j] = min((*dp)[i][j], 1 + dfs(node, j));
            }
        }

        return (*dp)[i][j];
    }

    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        dp = new vector<vector<int>>(n, vector<int>(n, mx));
        graph = new vector<vector<int>>(n);
        vis = new vector<bool>;

        // Construct the graph and initialize dp values
        for (const vector<int>& edge : edges) {
            (*graph)[edge[0]].push_back(edge[1]);
            (*graph)[edge[1]].push_back(edge[0]);
            (*dp)[edge[0]][edge[1]] = (*dp)[edge[1]][edge[0]] = 1;
        }

        // Perform DFS for all pairs of nodes
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                    (*vis).clear();
                    (*vis).resize(n, false);
                    (*vis)[i] = true;
                    (*dp)[i][j] = dfs(i, j);
            }
        }

        // Sum the distances for each node
        vector<int> ret(n);
        for (int i = 0; i < n; ++i) {
            ret[i] = accumulate((*dp)[i].begin(), (*dp)[i].end(), 0);
        }
        
        return ret;
    }
};