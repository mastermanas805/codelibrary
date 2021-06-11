#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int find(vector<int>& par, int i) {
        if (par[i] == i)
            return i;
        return par[i] = find(par, par[i]);
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> par(edges.size() + 1);
        int a = -1, b = -1;
        for (int i = 0; i < par.size(); ++i) par[i] = i;
        for (vector<int>& i: edges) {
            if (find(par, i[0]) != find(par, i[1]))
                par[find(par, i[0])] = find(par, i[1]);
            else {
                a = i[0];
                b = i[1];
            }
        }
        return {a, b};
    }
};


int main()
{
    vector<vector<int>> v = {
                             {9,10},
                             {5,8},
                             {2,6},
                             {1,5},
                             {3,8},
                             {4,9},
                             {8,10},
                             {4,10},
                             {6,8},
                             {7,9},
                            };
    Solution s;
    vector<int> ans  = s.findRedundantConnection(v);
    cout<<ans[0]<<" "<<ans[1]<<"\t";

};