#include <bits/stdc++.h>
using namespace std;

class graph
{
      protected:
        int v;   // No. of vertices
        // Pointer to an array containing adjacency lists
        vector<int> *adj;
      public:
          graph()
          {
                  cout<<"Enter No of Vertices \n";
                  cin>>v;
                  adj = new vector<int>[v];
          }

          void addEdge(int u, int v)
          {
                  adj[u].push_back(v);
                  adj[v].push_back(u);
          }

          void print()
          {    cout<<endl<<"Resultant Graph is"<<endl;
                  vector<int>::iterator j;
                  for(int i = 0; i < v; i++)
                  {     cout<<i<<" ";
                          for(j=adj[i].begin(); j < adj[i].end(); j++)
                          {
                                  cout<<*j<<" ";
                          }
                          cout<<endl;
                  }
          }

};
