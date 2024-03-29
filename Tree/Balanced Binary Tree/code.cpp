// https://leetcode.com/problems/balanced-binary-tree/


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
class Solution {
public:
    bool f = true;
    int heightBalance(TreeNode* root){
        if(root == NULL) return 0;
        int l = heightBalance(root->left), r = heightBalance(root->right);
        if(abs(l-r) > 1) f = false;
        return max(l,r)+1;
    }
    bool isBalanced(TreeNode* root) {
        heightBalance(root);
        return f;
    }
};