#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // using bfs
        int V = graph.size();
        vector<int> col(V,-1);
        
        for(int i=0;i<V;i++){ // Taking into consideration there can be unconnected components of graph
            if(col[i]==-1){
                queue<int> Q;
                Q.push(i);
                col[i] = 0;
                while(Q.size()){
                    int topE = Q.front();
                    for(auto E:graph[topE]){
                        if(col[E]==-1){
                            if(col[topE]==0)
                                col[E]=1;
                            else
                                col[E]=0;
                            Q.push(E);
                        } else if(col[E]==col[topE])//It means it is visted earlier and the colour of it is same as of parent
                            return false;
                    }
                    Q.pop();
                }
            }
        }
        return true;
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
