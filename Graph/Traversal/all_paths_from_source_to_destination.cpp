#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        
        vector<vector<int>> paths;
        int V = graph.size();
        stack<pair<vector<int>, vector<bool>>> s;
        vector<int> x;
        vector<bool> visited(V,0);
        x.push_back(0);
        visited[0] = 1;
        s.push({x, visited});
        
        while(!s.empty())
        {
            if(s.top().first.back() == V-1)
            {
                paths.push_back(s.top().first);
                s.pop();
            }
            
            else
            {
                vector<int> v = s.top().first;
                vector<bool> visited = s.top().second;
                visited[v.back()] = 1;
                s.pop();
                vector<int>::iterator i;
                for(i= graph[v.back()].begin(); i != graph[v.back()].end(); i++)
                  if(!visited[*i])
                    {
                        vector<int> x = v;
                        x.push_back(*i);
                        s.push({x, visited});
                    }
            }
        }

        return paths;
        
    }
};

int main()
{
    // vector<vector<int>> v = {
    //                             {4,3,1},
    //                             {3,2,4},
    //                             {3},
    //                             {4},
    //                             {}
    //                         };

    vector<vector<int>> v = {
                              {1,2,3},
                              {2},
                              {3},
                              {}
                            };

    Solution s;
    s.allPathsSourceTarget(v);
}