//https://leetcode.com/problems/path-sum-ii/
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
    void travel(TreeNode* root, int targetSum, vector<int>& s, vector<vector<int>>& v)
    {
        if(root == NULL) return;
        
        if(targetSum<0 && root->val > 0) targetSum+=root->val;
        else targetSum-=root->val;
        
        s.push_back(root->val);
        if(root->left == NULL && root->right == NULL) 
         {   
            if(targetSum == 0) {v.push_back(s);}
            s.pop_back();
            return;
        }
        
        travel(root->left,targetSum,s,v);
        travel(root->right,targetSum,s,v);
        s.pop_back();
    }
    
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> v;
        vector<int> s;
        travel(root,targetSum,s,v);
        return v;
    }
};

int main()
{
    TreeNode *t = new TreeNode(1);
    t->left = new TreeNode(-2);
    t->right = new TreeNode(3);
    
    Solution s;
    s.pathSum(t,-5);
  
}