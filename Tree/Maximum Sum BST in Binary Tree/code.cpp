//  https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/


class Node{ 
    public :
    int maxVal,minVal,sum;
    Node(int a,int b,int c){
        maxVal = a; minVal = b; sum = c;
    }
};

class Solution {
public: 
    int res = INT_MIN;
    Node process(TreeNode * curr){
        if(curr==nullptr){
            return Node(INT_MIN,INT_MAX,0);
        }
        auto left = process(curr->left);
        auto right = process(curr->right);
        if(left.maxVal<curr->val && right.minVal>curr->val){
            res = max(res,left.sum+right.sum+curr->val);
            return Node(max(curr->val,right.maxVal),min(curr->val,left.minVal),left.sum+right.sum+curr->val);           
        }
        return Node(INT_MAX,INT_MIN,max(left.sum,right.sum));
    }
    int maxSumBST(TreeNode* root) { 
        process(root);
        return max(0,res);
    }
};