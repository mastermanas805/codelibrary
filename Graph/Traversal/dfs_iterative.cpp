#include<bits/stdc++.h>
#include "graph.h"
using namespace std;

class dfsiterative: public graph
{
    public:
    queue<int> dfs(int n)
     {
         vector<bool> visited(v,0);
         stack<int> s;
         queue<int> q;
         int buff;
         s.push(n);
         vector<int>::iterator i;
         while(!s.empty())
          {
              buff = s.top();
              s.pop();
              if(!visited[buff])
                q.push(buff);
              visited[buff] = 1;

              for( i=adj[buff].begin();  i!=adj[buff].end(); i++)
                 if( !visited[*i] )
                    s.push(*i);
          }

          return q;
     }

     void printdfs(queue<int> q)
      {
          cout<<"DFS of Tree is"<<endl;
          while(!q.empty())
           {
               cout<<q.front()<<"\t";
               q.pop();
           }
      }
};

int main()
{
  int x;
  dfsiterative g;
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
  
  g.printdfs(g.dfs(0));

  return 0;
}