// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/

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
    int solve(TreeNode* root, int mx, int mn){
        if(root == NULL) return 0;
        mx = max(mx, root->val);
        mn = min(mn, root->val);
        return max({abs(mx-root->val), abs(mn-root->val), solve(root->left, mx, mn), solve(root->right, mx,mn)});
    }
    int maxAncestorDiff(TreeNode* root) {
        return solve(root, INT_MIN,INT_MAX);
    }
};