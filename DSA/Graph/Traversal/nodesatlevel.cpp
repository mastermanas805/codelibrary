#include<bits/stdc++.h>
#include "../headers/graph.h" 
using namespace std;

class levelnodescount: public graph
{
    public:
    int bfslevel(int n, int l)
     {
       vector<bool> visited(v,0);
       vector<int>  level(v,0);
       queue<int> q;
       q.push(n);
       level[n] = 0;
       vector<int>::iterator i;

       int x;

       while(!q.empty())
        {
          x = q.front();
          q.pop();

          if(!visited[x])
           {
             visited[x] = 1;
             for(i = adj[x].begin(); i!=adj[x].end(); i++)
               {
                 if(!visited[*i])
                  {
                    q.push(*i);
                    level[*i]++;
                  }
               }
           }
        }

        int count =0;
        for( i= level.begin(); i!=level.end(); i++)
         {
           if(*i == l)
              count++;
         }

         return count == 0? -1: count;
     }
      
};

int main()
{
  int x;
  levelnodescount g;
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
  cout<<g.bfslevel(0,2);

  return 0;
}