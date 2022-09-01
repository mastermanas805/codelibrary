// https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1

class Solution
{
	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int v, vector<vector<int>> adj[], int s)
    {
        vector<int> distance(v, INT_MAX);
        queue<pair<int,int>> q;
        q.push({s,0});
        distance[s] = 0;
        while(q.size()){
            int node= q.front().first, dis = q.front().second;
            q.pop();
            for(vector<int> i: adj[node]){
                if(dis + i[1] < distance[i[0]]){
                    distance[i[0]] = dis + i[1];
                    q.push({i[0], distance[i[0]]});
                }
            }
        }
        
        
        return distance;
    }
};