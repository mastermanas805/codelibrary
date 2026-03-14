---
attachments: [Clipboard_2021-05-21-15-01-13.png, Clipboard_2021-05-21-15-01-17.png, Clipboard_2021-05-21-15-01-20.png, Clipboard_2021-05-21-15-01-30.png]
title: Find a Root/Mother Vertex in a Graph
created: '2021-05-21T09:29:59.392Z'
modified: '2021-05-21T09:33:05.777Z'
---

# Find a Root/Mother Vertex in a Graph

What is a Mother Vertex? 
A mother vertex in a graph G = (V,E) is a vertex v such that all other vertices in G can be reached by a path from v.
Example : 

Input  : Below Graph
Output : 5

![](@attachment/Clipboard_2021-05-21-15-01-30.png)

There can be more than one mother vertices in a graph. We need to output anyone of them. For example, in the below graph, vertices 0, 1 and 2 are mother vertices. 
 
 ![](@attachment/Clipboard_2021-05-21-15-01-20.png)

- Case 1:- Undirected Connected Graph : In this case, all the vertices are mother vertices as we can reach to all the other nodes in the graph.
- Case 2:- Undirected/Directed Disconnected Graph : In this case, there is no mother vertices as we cannot reach to all the other nodes in the graph.
- Case 3:- Directed Connected Graph : In this case, we have to find a vertex -v in the graph such that we can reach to all the other nodes in the graph through a directed path.


Algorithm : 

  1. Do DFS traversal of the given graph. While doing traversal keep track of last finished vertex ‘v’. This step takes O(V+E) time.
  2. If there exist mother vertex (or vertices), then v must be one (or one of them). Check if v is a mother vertex by doing DFS/BFS from v. This step also takes O(V+E) time.

  ```cpp
  
  // C++ program to find a mother vertex in O(V+E) time
#include <bits/stdc++.h>
using namespace std;

class Graph
{
	int V; // No. of vertices
	list<int> *adj; // adjacency lists

	// A recursive function to print DFS starting from v
	void DFSUtil(int v, vector<bool> &visited);
public:
	Graph(int V);
	void addEdge(int v, int w);
	int findMother();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, vector<bool> &visited)
{
	// Mark the current node as visited and print it
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

// Returns a mother vertex if exists. Otherwise returns -1
int Graph::findMother()
{
	// visited[] is used for DFS. Initially all are
	// initialized as not visited
	vector <bool> visited(V, false);

	// To store last finished vertex (or mother vertex)
	int v = 0;

	// Do a DFS traversal and find the last finished
	// vertex
	for (int i = 0; i < V; i++)
	{
		if (visited[i] == false)
		{
			DFSUtil(i, visited);
			v = i;
		}
	}

	// If there exist mother vertex (or vetices) in given
	// graph, then v must be one (or one of them)

	// Now check if v is actually a mother vertex (or graph
	// has a mother vertex). We basically check if every vertex
	// is reachable from v or not.

	// Reset all values in visited[] as false and do
	// DFS beginning from v to check if all vertices are
	// reachable from it or not.
	fill(visited.begin(), visited.end(), false);
	DFSUtil(v, visited);
	for (int i=0; i<V; i++)
		if (visited[i] == false)
			return -1;

	return v;
}

// Driver program to test above functions
int main()
{
	// Create a graph given in the above diagram
	Graph g(7);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(4, 1);
	g.addEdge(6, 4);
	g.addEdge(5, 6);
	g.addEdge(5, 2);
	g.addEdge(6, 0);

	cout << "A mother vertex is " << g.findMother();

	return 0;
}

  ```
