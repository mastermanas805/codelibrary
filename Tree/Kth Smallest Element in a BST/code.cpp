/*
src = https://leetcode.com/problems/kth-smallest-element-in-a-bst/
concept = in order traversal
*/

class Solution {
public:
    int ans = -1;
    int kthSmallest(TreeNode* root, int k) {
        travel(root,k);
        return this->ans;
    }
    
    void travel(TreeNode* root, int& k)
    {
        if(root== NULL) return;
        travel(root->left, k);
        k--;
        if(k == 0)
        {
            this->ans = root->val;
            return;
        }
        travel(root->right, k);
    }
};