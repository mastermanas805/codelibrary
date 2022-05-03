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
    
    ListNode* reverse(ListNode* head)
    {
        ListNode *x, *y, *prev = NULL;
        x = head;
        
        while(x)
        {
          y = x->next;
          x->next = prev;
          prev = x;
          x = y;
        }
        
        return prev;
    }
    
    bool isPalindrome(ListNode* head) {
            if(!head->next) return 1;
        
            int n =0;
            ListNode *f, *r, *fptr;
            f = r = fptr = head;
            fptr = fptr->next;

            while(fptr && fptr->next)
            {
                r = r->next;
                fptr=fptr->next;
                if(fptr) fptr=fptr->next;
            }

            fptr = r;
            r = r->next;
            fptr->next = NULL;
            r = reverse(r);

            while(f && r)
            {
                if(f->val != r->val)
                    return 0;
                f = f->next;
                r = r->next;
            }

            return 1;

        }
};