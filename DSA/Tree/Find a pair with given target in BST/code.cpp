// https://practice.geeksforgeeks.org/problems/find-a-pair-with-given-target-in-bst

void inorder(struct Node *root, vector<int>& v){
        if(root == NULL) return;
        inorder(root->left,v);
        v.push_back(root->data);
        inorder(root->right,v);
    }
    
    int isPairPresent(struct Node *root, int target)
    {
        vector<int> v;
        inorder(root, v);
        
        int left = 0, right = v.size()-1;
        
        while(left <= right){
            if(v[left]+v[right] == target) return 1;
            
            if(v[left]+v[right] < target) left++;
            else right--;
        }
        
        return 0;
        
    }