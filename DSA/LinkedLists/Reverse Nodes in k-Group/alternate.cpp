// struct ListNode {
//      int val;
//      ListNode *next;
//      ListNode() : val(0), next(nullptr) {}
//      ListNode(int x) : val(x), next(nullptr) {}
//      ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
public:
    
    
    void reverseList(ListNode* head, ListNode* toe, ListNode* front, ListNode* rear)
    {
        ListNode *x, *ptr = head;
        while(ptr!=rear && ptr!=NULL)
        {
            x = ptr->next;
            ptr->next = front;
            front = ptr;
            ptr = x;
        }
        
        head->next = rear;
    }
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        if(k<=1) return head;
        
        ListNode *sptr, *fptr, *front = NULL, *nxt;
        int count;
        sptr = fptr = head;
        
        while(fptr != NULL)
        {
            count=1;
            fptr = sptr;
            while(count<k)
            {
                if(fptr == NULL) return head;
                
                fptr = fptr->next;
                count++;
            }
            if(fptr == NULL) return head;
            nxt = fptr->next;
            reverseList(sptr, fptr, front, nxt);
            
            if(front == NULL) head = fptr;
            else front->next = fptr;
            front = sptr;
            sptr = fptr = nxt;
        }
        
        return head;
    }
};