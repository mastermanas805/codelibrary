//https://leetcode.com/problems/kth-ancestor-of-a-tree-node/
#include<bits/stdc++.h>
using namespace std;

#define pb push_back

class TreeAncestor {
public:
    vector<vector<int>>v;
    TreeAncestor(int n, vector<int>& parent) {
        vector<vector<int>> par(n, vector<int>(20));
        for (int i = 0; i < n; i++) par[i][0] = parent[i];

        for (int j = 1; j < 20; j++) 
            for (int i = 0; i < n; i++) 
                if (par[i][j - 1] == -1) par[i][j] = -1;
                else par[i][j] = par[par[i][j - 1]][j - 1];
        
        swap(v, par);
    }
    int getKthAncestor(int node, int k) {
        for (int i = 0; i < 20; i++) {
            if ((k >> i) & 1) {
                node = v[node][i];
                if (node == -1) return -1;
            }
        }
        return node;
    }
};

int main()
{
    vector<int> v = {-1, 0, 0, 1, 1, 2, 2};
    TreeAncestor *T = new TreeAncestor(7,v );
    vector<vector<int>> t = {{3, 1}, {5, 2}, {6, 3}};
    for(int i=0; i<t.size(); i++)
       cout<<T->getKthAncestor(t[i][0],t[i][1]);

    return 0;
}
