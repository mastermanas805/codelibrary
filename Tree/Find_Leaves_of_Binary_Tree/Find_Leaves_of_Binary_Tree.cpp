// https://leetcode.com/problems/find-leaves-of-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <vector>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> v;

    Solution(){
        v =  vector<vector<int>>(101);
    }

    int travel(TreeNode* root){
        int l,r,ret;
        l = root->left!=NULL?travel(root->left):0;
        r = root->right!=NULL?travel(root->right):0;

        ret = max(l,r)+1;
        v[ret].push_back(root->val);
        return ret;
    }

    vector<vector<int>> findLeaves(TreeNode* root) {
        travel(root);
        vector<vector<int>> v;
        for(int i=1;i<101;i++){
            if(this->v[i].size() == 0)
                break;
            v.push_back(this->v[i]);
        }
        
        return v;
    }
};