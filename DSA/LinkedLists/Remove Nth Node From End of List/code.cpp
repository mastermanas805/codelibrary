//https://leetcode.com/problems/remove-nth-node-from-end-of-list/

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int count = 0;
        ListNode *temp=head, *nptr, *prev;
        nptr = head;
        prev = nullptr;
        while(temp!= nullptr)
        {
            if(count>n-1)
            {
                prev = nptr;
                nptr = nptr->next;
            }
            temp = temp->next;
            count++;
        }
        
        if(prev == nullptr) head = nptr->next;
        else prev->next = nptr->next;
        nptr->next = nullptr;
        delete(nptr);
        
        return head;
    }
};