#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> n(graph.size(),-1);
        vector<bool> visited(graph.size(),0);
        int x, src = 0, size = graph.size();
        stack<int> s;
        bool flag  = 1;

        while(flag)
        {    
            s.push(src);

            if(n[src] == -1)
                n[src] = 1;

            while(!s.empty())
            {
                x = s.top();
                visited[x] = 1;
                s.pop();
                
                for(auto i:graph[x])
                {
                    if(n[x] == n[i])
                            return 0;
                    if(!visited[i])
                    {    
                        n[i] = !n[x];
                        s.push(i);
                    }
                }
            }
           
           for(int i = 0; i< size && flag; i++)
             flag&= n[i] == -1?0:1;
            
            flag = !flag;
            src++;
        }

        return 1;
    }
};


int main()
{
    // vector<vector<int>> v = {
    //                     {1,3},
    //                     {0,2},
    //                     {1,3},
    //                     {0,2}
    //                 };

    vector<vector<int>> v = {
                                {},
                                {2,4,6},
                                {1,4,8,9},
                                {7,8},
                                {1,2,8,9},
                                {6,9},
                                {1,5,7,8,9},
                                {3,6,9},
                                {2,3,4,6,9},
                                {2,4,5,6,7,8}
                            };

    Solution s;
    cout<<"Graph is "<<((s.isBipartite(v) == 1)? "":"not")<<" Bipartile"<<endl;
}