#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        Node *parent, *left, *right;
        int size;

    Node(){
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
        this->size = 1;
    }
};

int calculateSize(Node* root){
    if(root == NULL)
        return 0;
    root->size += calculateSize(root->left) + calculateSize(root->right);
    return root->size;
}


class Solution {
public:
    int countHighestScoreNodes(vector<int>& parents) {
        int n = parents.size();
        Node nodes[n];
        Node* root;
        
       
        
        for(int i=0;i<n;i++){
            if(parents[i] == -1){
                root = &nodes[i];
                continue;
            }
            nodes[i].parent = &nodes[parents[i]];
            if(nodes[parents[i]].left == NULL){
                nodes[parents[i]].left = &nodes[i];
            }else if(nodes[parents[i]].right == NULL){
                nodes[parents[i]].right = &nodes[i];
            }
        }

        calculateSize(root);
        map<long,long> mp;
        long mx = 0;
        for(Node node: nodes){
            long prod = 1;
            if(root->size - node.size > 0)
                prod*= root->size - node.size;
            if(node.left)
                prod*=node.left->size;
            if(node.right)
                prod*=node.right->size;

            mp[prod]++;
            mx = max(mx, prod);
        
        }
        return mp[mx];
    }
};