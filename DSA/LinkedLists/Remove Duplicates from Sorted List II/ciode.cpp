//https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

#include<bits/stdc++.h>
using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 

 ListNode* insert(int n)
{
  int val;
  ListNode *root,*temp;
  cin>>val;
  root = new ListNode(val);
  temp = root;
  
  while(--n) {cin>>val; temp->next = new ListNode(val); temp = temp->next;}

  return root;
}

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode *root = head,*prev = nullptr;
        while(root != nullptr)
        {
            ListNode *x = root;
            while(root!=nullptr && root->next != nullptr && root->val == root->next->val)
                root = root->next;
            if(x != root )
            {
                if(prev == nullptr) head = root->next,  root = root->next;
                else prev->next = root->next, root = root->next;
            }

            else prev = root, root = root->next;
        }
        
        return head;
    }
};

int main()
{
    int n;
    cin>>n;
    ListNode *l = insert(n);
    
    Solution s;
     ListNode *end = s.deleteDuplicates(l);
     while(end != NULL) {cout<<end->val<<"->"; end = end->next;}
    
    
}