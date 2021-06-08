// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


class Solution 
{
    public:
	//Function to return a list containing the DFS traversal of the graph.
	vector<int> final;
	
	void traverse(int n, vector<int> adj[], vector<int> flag)
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
	    /*
	    
	    [
	    0th [1,2,3,4]
	    1st [0,4,5,7]
	    ...
	    ...
	    ]
	    
	    Algo-
	    adj // e edges 
	    flag[v] // check of visited
	    stack s
	    s.push(root)
	    flag[root] = 1
	    while(s not empty)
	     {
	         temp = s.top();
	         s.pop();
	         v.push temp
	         
	         for(j in temp.adjacent nodes):
	               if(!f[j]) //j not visited
	                  
	     }
	    */
	    
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