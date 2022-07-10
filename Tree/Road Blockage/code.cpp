#include <bits/stdc++.h>
using namespace std;
#define pb push_back

class Solution {
  public:
    vector<int> adj[100005];
    int level[100005] = {0};
    vector<int> eulerTour;
    bool visited[100005] = {0};
    map<int,int> start, end;
    
    int max_ele(int l, int r)
    {
        int mx = INT_MIN;
        for(int i = l; i<r; i++) mx = max(mx, level[eulerTour[i]]);
        return mx>0? mx:0;
    }
    
    void dfs(int node, int l = 0){
        level[node] = l;
        eulerTour.push_back(node);
        visited[node] = 1;
        if(start.find(node) == start.end()) start[node] = eulerTour.size()-1;
        for(auto i: adj[node])
            if(!visited[i])
                dfs(i, l+1);
        
        eulerTour.push_back(node);
        end[node] = eulerTour.size()-1;
    }
    
    vector<int> solve(int N, int Q, vector<vector<int> > &Edge,
                      vector<vector<int> > &query) {
        
        for(int i=0; i<Edge.size(); i++) 
            adj[Edge[i][0]].pb(Edge[i][1]), adj[Edge[i][1]].pb(Edge[i][0]);
        
        dfs(0);
        int i = 0;
            
        
        int prefix[eulerTour.size()] = {0}, suffix[eulerTour.size()] = {0};
        int mx1 = INT_MIN, mx2 = INT_MIN;
        for(int i=0; i<eulerTour.size(); i++){
            mx1 = max(mx1, level[eulerTour[i]]);
            prefix[i] = mx1;
            mx2 = max(mx2, level[eulerTour[eulerTour.size() - 1 - i]]);
            suffix[eulerTour.size() - 1 - i] = mx2;
        }
        
        
        vector<int> res;
        int x;
        for(int i=0; i<query.size(); i++)
        {
            x = level[query[i][0]] > level[query[i][1]]? query[i][0]: query[i][1];
            x = max(prefix[start[x] - 1], suffix[end[x] + 1]);
            res.push_back(x);
        }
        
        
        return res;
    }
};


// { Driver Code Starts.

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        vector<vector<int> > Edge(N - 1, vector<int>(2));

        for (int i = 0; i < N - 1; i++) cin >> Edge[i][0] >> Edge[i][1];

        vector<vector<int> > query(Q, vector<int>(2));

        for (int i = 0; i < Q; i++) cin >> query[i][0] >> query[i][1];

        Solution ob;
        vector<int> annswer = ob.solve(N, Q, Edge, query);

        for (auto it : annswer) cout << it << " ";
        cout << "\n";
    }
    return 0;
}
  // } Driver Code Ends