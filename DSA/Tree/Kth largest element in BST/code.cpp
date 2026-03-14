//  https://practice.geeksforgeeks.org/problems/kth-largest-element-in-bst

class Solution
{
    public:
    int ans = -1;
    void find(Node *root, int& K)
    {
        if(root == NULL) return;
        find(root->right, K);
        K--;
        if(K == 0) ans = root->data;
        find(root->left, K);
    }
    
    int kthLargest(Node *root, int K)
    {
        find(root, K);
        return ans;
    }
};