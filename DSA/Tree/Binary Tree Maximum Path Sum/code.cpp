//  https://leetcode.com/problems/binary-tree-maximum-path-sum/

//eficient
int findMaxPathSum(TreeNode * root, int & maxi) {
      if (root == NULL) return 0;

      int leftMaxPath = max(0, findMaxPathSum(root -> left, maxi));
      int rightMaxPath = max(0, findMaxPathSum(root -> right, maxi));
      int val = root -> val;
      maxi = max(maxi, (leftMaxPath + rightMaxPath) + val);
      return max(leftMaxPath, rightMaxPath) + val;

    }
    int maxPathSum(TreeNode* root) {
          int maxi = INT_MIN;
          findMaxPathSum(root, maxi);
          return maxi;
    }
};

//alternative


class Solution {
public:
    int mx = INT_MIN;
    
    int travel(TreeNode* root)
    {
        if(root == NULL) return -1001;
        
        int l,r;
        l = travel(root->left);
        r = travel(root->right);
        mx = max({mx, root->val, l, r, l+r+root->val, l + root->val, r+ root->val});
        
        return max({root->val, l + root->val, r + root->val});
    }
    
    int maxPathSum(TreeNode* root) {
        if(root == NULL) return 0;
        if(root->left  == NULL && root->right == NULL) return root->val;
        travel(root);
        return mx;
    }
};