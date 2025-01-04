// https://leetcode.com/problems/cut-off-trees-for-golf-event

class Solution {
public:
    int m,n;
    vector<pair<int,int>> directions = {{0,-1}, {-1,0}, {0,1}, {1,0}};
    int cutOffTree(vector<vector<int>> forest) {
        m = forest[0].size(); n = forest.size();
        priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;

        for(int i=0; i<n; i++){
            for(int j=0;j<m; j++){
                if(forest[i][j] <= 1) continue;
                pq.push({forest[i][j], {i,j}});
            }
        }

        pair<int,int> src = {0,0};
        int sum = 0;
        while(!pq.empty()) {
            auto dst = pq.top();
            pq.pop();
            int steps = minDist(forest, src, dst.second);
            if(steps == -1) return -1;
            sum+=steps;
            src = dst.second;
        }

        return sum;
    }

    int minDist(vector<vector<int>>& forest, pair<int,int> src, pair<int,int> dst){
        vector<vector<bool>> visited(n, vector<bool>(m,false));
        queue<pair<int,int>> q;
        q.push(src);
        visited[src.first][src.second] = 1;
        int steps = 0;

        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                pair<int,int> node = q.front();
                q.pop();
                if(node == dst) return steps;
                for(auto neighbour: directions) {
                    pair<int,int> dst = {
                                            node.first + neighbour.first, 
                                            node.second + neighbour.second
                                        };
                    if(dst.first < 0 || dst.first >= n || dst.second < 0 || dst.second >= m || 
                    visited[dst.first][dst.second] || forest[dst.first][dst.second] == 0) 
                        continue;
                    q.push(dst);
                    visited[dst.first][dst.second] = 1;
                }
            }
            steps++;
        }

        return -1;
    }
};