#include<bits/stdc++.h>
using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
    public:
        int deepestLeavesSum(TreeNode* root) 
        {
            queue<TreeNode*> q;
            int sum,sz;
            q.push(root);
            while(!q.empty())
            {
                sum =0;
                sz = q.size();
                for(int i=0; i<sz; i++)
                {
                    TreeNode* x = q.front();
                    q.pop();
                    sum+=x->val;
                    if(x->left != NULL) q.push(x->left);
                    if(x->right != NULL) q.push(x->right);
                }
            }
            return sum;
        }
};

int main()
{
    TreeNode* t = new TreeNode(1);
    t->left = new TreeNode(2);
    t->right = new TreeNode(3);
    t->left->left = new TreeNode(4);
    t->left->right = new TreeNode(5);
    t->right->left = new TreeNode(7);
    t->right->right = new TreeNode(6);
    t->right->right->right = new TreeNode(8);

    Solution s;
    cout<<s.deepestLeavesSum(t)<<endl;
}