#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int target;
    vector <vector <int> > res;
    vector <int> temp;
    
    void dfs(vector<vector<int>>& graph,int curr=0){
        temp.push_back(curr);
        if (curr==target)
            res.push_back(temp);
        else{
            for (auto i:graph[curr]){
                dfs(graph,i);
            }
        }
        temp.pop_back();
    }
    
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        target=graph.size()-1;
        dfs(graph);
        return res;
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
     vector<vector<int>> paths = s.allPathsSourceTarget(v);
     vector<vector<int>>::iterator i;
     vector<int>::iterator j;
     for(int i=0; i<paths.size(); i++)
      {
          for(j = paths[i].begin(); j!=paths[i].end(); j++)
            cout<<*j<<"->";
          cout<<"end"<<endl;
      }
}