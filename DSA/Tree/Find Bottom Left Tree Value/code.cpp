// https://leetcode.com/problems/find-bottom-left-tree-value/

class Solution {
public:
    int ans=-1;
     int findBottomLeftValue(TreeNode* root) {
         queue<TreeNode*>q;
          q.push(root);
          while(!q.empty())
         {
                 int size=q.size();
                 for(int i=0;i<size;i++)
                 {
                     TreeNode*t=q.front();
                     q.pop();
                     if(i==0)
                      ans=t->val;
                     if(t->left)
                         q.push(t->left);
                     if(t->right)
                         q.push(t->right);
                 }
             
            
         }
         return ans;
     }
};