#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findCircleNum(vector<vector<int>>& g) {
        int c=0;
        for(int i=0;i<g.size();i++)
        {
            if(g[i][i])
            {
                c++;
                dfs(g,i);
            }
        }
        return c;
    }
    void dfs(vector<vector<int>>& g,int x)
    {
        g[x][x]=0;
        for(int i=0;i<g[x].size();i++)
        {
            if(g[x][i] && g[i][i])
                dfs(g,i);
        }
        return;
    }
};

int main()
{
    vector<vector<int>> isConnected = {
                                       {1,0,0},
                                       {0,1,0},
                                       {0,0,1}
                                      };
    Solution s;
    cout<<"No of Provinces are: "<<s.findCircleNum(isConnected)<<endl;

}