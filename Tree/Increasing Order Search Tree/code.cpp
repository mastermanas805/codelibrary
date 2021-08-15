#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
     int val;
     TreeNode* left;
     TreeNode* right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    TreeNode* increasingBST(TreeNode* root, TreeNode* tail = NULL) {
        if (!root) return tail;
        TreeNode* res = increasingBST(root->left, root);
        root->left = NULL;
        root->right = increasingBST(root->right, tail);
        return res;
    }
    
};

int main()
{
    TreeNode *t = new TreeNode(5);
    t->left = new TreeNode(3);
    t->left->left = new TreeNode(2);
    t->left->left->left = new TreeNode(1);
    t->left->right = new TreeNode(4);
    
    t->right = new TreeNode(6);
    t->right->right = new TreeNode(8);
    t->right->right->left = new TreeNode(7);
    t->right->right->right = new TreeNode(9);
    
    Solution s;
    TreeNode *ans  = s.increasingBST(t);
    while(ans) {cout<<ans->val<<"->"; ans=ans->right;}
  
}