// https://leetcode.com/problems/maximum-width-of-binary-tree/

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
    int widthOfBinaryTree(TreeNode* root) {
        long ans = INT_MIN, x;
        queue<pair<TreeNode*, long>> q;
        q.push({root, 0});
        while(!q.empty()){
            int sz = q.size();
            long x,y;
            for(int i=0;i<sz;i++){
                TreeNode* node = q.front().first;
                int index = q.front().second;
                q.pop();
                if(i == 0) x = index;
                if(i == sz-1) y = index;
                
                if(node->left != NULL) q.push({node->left, (long long)2*index+1 });
                if(node->right != NULL) q.push({node->right, (long long)2*index+2});
            }
            ans = max(ans, y-x+1);
        }
        
        return ans;
    }
};