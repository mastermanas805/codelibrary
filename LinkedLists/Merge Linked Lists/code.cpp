//https://leetcode.com/problems/merge-two-sorted-lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *root = new ListNode();
        ListNode *temp = root;
        
        while(l1 != nullptr && l2!=nullptr)
        {
            if(l1->val < l2->val)
            {    
                temp->next = new ListNode(l1->val);
                l1 = l1->next;
            }
            
            else
            {    
                temp->next = new ListNode(l2->val);
                l2 = l2->next;
            }
            
            temp = temp->next;
        }
        
        if(l1 != nullptr) temp->next = l1;
        if(l2 != nullptr) temp->next = l2;
        
        
        return root->next;
    }
};