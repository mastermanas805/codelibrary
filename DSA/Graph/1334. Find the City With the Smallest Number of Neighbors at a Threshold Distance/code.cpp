class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
        for(vector<int> i: edges) {
            int u = i[0], v = i[1], cost = i[2];
            graph[u][v] = graph[v][u] = cost;
        }

        for(int i=0;i<n;i++) graph[i][i] = 0;

        for(int k = 0; k<n;k++){
            for(int i=0; i<n; i++){
                for(int j=0; j<n;j++){
                    if( graph[i][k] == INT_MAX || graph[k][j] == INT_MAX) continue;
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }

        vector<int> reaches(n,0);

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                reaches[i] += i!=j && graph[i][j] <= distanceThreshold;
            }
        }

        int mx = *min_element(reaches.begin(), reaches.end());
        for(int i=n-1; i>=0; i--) {
            if(mx == reaches[i]) return i;
        }

        return 0;
    }
};