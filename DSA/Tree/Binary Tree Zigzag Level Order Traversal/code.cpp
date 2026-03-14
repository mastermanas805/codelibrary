//  https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
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
#define pb push_back
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == NULL) return {};
        vector<vector<int>> ans;
        int n;
        queue<TreeNode*> q;
        q.push(root);
        bool f = 1;
        
        while(!q.empty())
        {
            f=!f;
            n = q.size();
            vector<int> v;
            for(int i=0;i<n;i++)
            {
                TreeNode* x = q.front();
                q.pop();
                if(f) v.insert(v.begin(), x->val); else v.pb(x->val);
                if(x->left!=NULL) q.push(x->left);
                if(x->right!=NULL) q.push(x->right);
            }
            ans.pb(v);
        }
        
        return ans;
    }
};