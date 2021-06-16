#include<bits/stdc++.h>
#define max 10
using namespace std;
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
   Node* cloneGraph(Node* node) {
        
        if(node == NULL) return NULL;
        
        auto itr = mapp.find(node);
        if(itr != mapp.end())
            return itr->second;
        
        Node* new_node = new Node(node->val);
        mapp[node] = new_node;
        for(auto n : node->neighbors)
            new_node->neighbors.push_back(cloneGraph(n));
        
        return new_node;
    }
    
    unordered_map<Node*, Node*> mapp;
};

int main()
{
    vector<vector<int>> v = {
                              {2,4},
                              {1,3},
                              {2,4},
                              {1,3}
                            };
    Solution s;

    vector<Node*> nodes(max);
    for(int i=0; i<max; i++) nodes[i] = new Node(i);

    for(int i=0;i<v.size();i++)
     {
         for(int j=0; j<v[i].size(); j++)
           nodes[i]->neighbors.push_back(nodes[j]);              
     }

     Node* ans = s.cloneGraph(nodes[0]);
}