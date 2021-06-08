#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

class cores: public graph
 {
   int k;
   bool flag;
  public:
   cores()
    {
      cout<<"Enter No of Cores"<<endl;
      cin>>k;
    }

    void kcores()
      {
        flag = 1;
        vector<vector<int>> nodes;
        vector<int> temp;
        //Maintaing list of nodes with degree < K
        for(int i = 0; i<v;i++)
           if(adj[i].size() < k && adj[i].size()>0)
           {
             flag = 0;
             temp = adj[i];
             temp.insert(temp.begin(),i);
             nodes.push_back(temp);
           }
              
        

        std::vector<int>::iterator it;
        // Deleting nodes with degree < K
        for(int i=0;i<nodes.size();i++)
           {
             for(int j=1;j<nodes[i].size();j++)
              {
                it = find(adj[nodes[i][0]].begin(), adj[nodes[i][0]].end(), nodes[i][j]);
                if(it != adj[nodes[i][0]].end())
                  adj[nodes[i][0]].erase(it);
                
                it = find(adj[nodes[i][j]].begin(), adj[nodes[i][j]].end(), nodes[i][0]);
                if(it != adj[nodes[i][j]].end())
                  adj[nodes[i][j]].erase(it);
                 
              }
           }

          if(!flag)
             this->kcores();

      }
 
 };

int main()
{
  cores g;
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);
  g.addEdge(1, 5);
  g.addEdge(2, 3);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(2, 6);
  g.addEdge(3, 4);
  g.addEdge(3, 6);
  g.addEdge(3, 7);
  g.addEdge(4, 6);
  g.addEdge(4, 7);
  g.addEdge(5, 6);
  g.addEdge(5, 8);
  g.addEdge(6, 7);
  g.addEdge(6, 8);
  g.kcores();
  g.print();
}
