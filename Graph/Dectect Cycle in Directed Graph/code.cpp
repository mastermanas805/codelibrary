#include <bits/stdc++.h>
using namespace std;


bool detectCycle(int src, vector<vector<int>>& edges, vector<int>& color)
{
    color[src] = 1;
    for(auto i: edges[src])
    {
        if(color[i] == 1)
           return 1;
        
        else if(!color[i] && detectCycle(i, edges, color))
               return 1;
    }    
    color[src] = 2;
    return 0;
}

bool cycleInGraph(vector<vector<int>> edges) 
{
	vector<int> color(edges.size(),0);
	
	for(int i =0; i<edges.size(); i++)
	  if(!color[i] && detectCycle(i, edges, color))
		    return 1;
  
  return 0;
}


int main()
{
    vector<vector<int>> v = {
                                {1,2},
                                {2},
                                {}
                            };
    cout<<cycleInGraph(v);
}