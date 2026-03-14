// https://practice.geeksforgeeks.org/problems/topological-sort/1

class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	void findtoposort(int node, vector<int>& vis, stack<int>& st,vector<int> adj[]){
	    vis[node] = 1;
	    for(auto it: adj[node])
	        if(!vis[it]) findtoposort(it, vis, st, adj);\
	    
	    st.push(node);
	}
	vector<int> topoSort(int v, vector<int> adj[]) 
	{
	    stack<int> st;
	    vector<int> vis(v, 0);
	    
	    for(int i=0;i<v;i++)
	        if(!vis[i]) findtoposort(i, vis, st, adj);
	    
	    vector<int> ret;
	    while(!st.empty()){
	        ret.push_back(st.top());
	        st.pop();
	    }
	    
	    return ret;
	    
	}
};