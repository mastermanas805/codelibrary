#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        
        vector<bool> reachable(n,0);
        vector<int> set;
        
        for(int i=0; i<edges.size(); i++)
        {
            reachable[edges[i][1]] = 1;
        }
        
        for(int i = 0; i < n;i++)
            if(!reachable[i])
                set.push_back(i);
        return set;
    }
};

int main()
{
    int n = 6;
    vector<vector<int>> input = {
                                  {0,1},
                                  {0,2},
                                  {2,5},
                                  {3,4},
                                  {4,2}
                                };
    Solution s;
    vector<int> output = s.findSmallestSetOfVertices(n,input);
    vector<int>::iterator i;
    cout<<"\nMinimum Set is {";
    for(i = output.begin(); i!=output.end(); i++)
      cout<<*i<<",";
    cout<<"}"<<endl;

}