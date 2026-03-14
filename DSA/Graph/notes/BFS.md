---
title: BFS
created: '2021-05-20T05:15:16.454Z'
modified: '2021-05-20T05:18:53.848Z'
---

# BFS

## Algo

```
	      n = no of nodes
	      int adj[n] // Adjacent Lists
	      bool flag[n] //flag for visited nodes
	      for i in (0,n):
	          falg[i] = 0;
	      vector<int> v;
	      queue q;
	      v.push root
	      q.push root;
        flag[root] = 1;
	      while(q not empty):
	        {
	            temp = q.front
	            q.pop()
	            for(j in temp.adjacent nodes):
	               if(!f[j]) //j not visited
	                  v.push j
	        }
	      return v
```

Input
```
5 4
0 1 
0 2
0 3 
2 4
```
Output
```
0 1 2 3 4 
```

```cpp

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends



#include <queue>
class Solution
{
    public:
    //Function to return Breadth First Traversal of given graph.
	vector<int>bfsOfGraph(int v, vector<int> adj[])
	{
	    
	    
	    int i,j,temp;
	    vector<int> child, flag(v,0);
	    
	     
	    flag[0] = 1;
	    queue<int> q;
	    q.push(0);
	    
	    while(!q.empty())
	     {
	          temp = q.front();
	          child.push_back(temp);
	          q.pop();
	          
	          for(i=0;i<adj[temp].size();i++)
	           {
	               if(!flag[adj[temp][i]])
	                  {
	                      flag[adj[temp][i]] = 1;
	                      q.push(adj[temp][i]);
	                  }
	           }
	     }
	    
	    return child;
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
    // 		adj[v].push_back(u);
    	}
        // string s1;
        // cin>>s1;
        Solution obj;
        vector<int>ans=obj.bfsOfGraph(V, adj);
        for(int i=0;i<ans.size();i++){
        	cout<<ans[i]<<" ";
        }
        cout<<endl;
	}
	return 0;
}  // } Driver Code Ends
```
