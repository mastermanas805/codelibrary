#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mem[10001];
    
    bool dp(vector<vector<int>>& graph, int n)
    {
        if(mem[n] >= 0)
            return mem[n];
        
        if(mem[n] == -2)
            return 0; // It tells that n is in the visited stack of path and shoul not repeat
        mem[n] = -2;
        bool q = 1;
        for(auto i:graph[n])
            if(q)
                q &= dp(graph, i);
        
        return mem[n] = q;
    }
    
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        memset(mem, -1, sizeof(mem));
        
        vector<int> res;
        
        for(int i=0;i<graph.size();i++)
            if(dp(graph, i))
                res.push_back(i);
        
        return res;
    }
};

int main()
{
    vector<vector<int>> graph = {
                                  {1,2},
                                  {2,3},
                                  {5},
                                  {0},
                                  {5},
                                  {},
                                  {}
                                };

    // vector<vector<int>> graph = {
    //                                 {},
    //                                 {0,2,3,4},
    //                                 {3},
    //                                 {4},
    //                                 {}
    //                              };
    
    Solution s;
    vector<int> ans = s.eventualSafeNodes(graph);

    cout<<endl<<"[ ";
    for(auto i:ans)
     cout<<i<<", ";
    
    cout<<"]"<<endl;

}