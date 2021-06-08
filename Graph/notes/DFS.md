---
title: DFS
created: '2021-05-20T06:39:51.004Z'
modified: '2021-05-20T06:46:22.708Z'
---

# DFS

## Algo

```
output
traverse(node, adjacents, flag):
   output.push(node);
   flag[node] = 1;
   for(i in adjacent nodes)
     if(i not visited)
        traverse(i, adjacents, flag)

dfs(graph, adjacents)
    flag[no of nodes in graph]
    for i in flag:
       i = 0
    
    traverse(graph.root, adjacents, flag)
```

```cpp
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


class Solution 
{
    public:
	//Function to return a list containing the DFS traversal of the graph.
	vector<int> final;
	
	
	void traverse(int n, vector<int> adj[], vector<int> &flag)
	 {
	     final.push_back(n);
	     flag[n] = 1;
	     int i;
	     for(i=0;i<adj[n].size();i++)
	         if(!flag[adj[n][i]])
	            traverse(adj[n][i] ,adj ,flag);
	 }
	 
	vector<int>dfsOfGraph(int v, vector<int> adj[])
	{
	    final.clear();
	    vector<int> flag(v,0);
	    traverse(0,adj,flag);
	    return final;
	}
};

// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
    	cin >> V >> E;

    	vector<int> adj[V];

    	for(int i = 0; i < E; i++)
    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    		adj[v].push_back(u);
    	}
        // string s1;
        // cin>>s1;
        Solution obj;
        vector<int>ans=obj.dfsOfGraph(V, adj);
        for(int i=0;i<ans.size();i++){
        	cout<<ans[i]<<" ";
        }
        cout<<endl;
	}
	return 0;
}  // } Driver Code Ends
```
