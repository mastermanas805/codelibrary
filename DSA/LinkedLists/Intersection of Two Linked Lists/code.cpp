// https://leetcode.com/problems/intersection-of-two-linked-lists/


class Solution {
public:
    ListNode *getIntersectionNode(ListNode *h1, ListNode *h2) {
        int n = 0, m = 0;
        ListNode *ptr;
        ptr = h1;
        while(ptr) ptr=ptr->next, n++;
        
        ptr = h2;
        while(ptr) ptr=ptr->next, m++;
        
        if(n<m) swap(n,m), swap(h1,h2);
        
        for(int i=0; i<n-m; i++)
            h1 = h1->next;
        
        while(h1!=NULL && h2!=NULL)
        {
            if(h1 == h2) return h1;
            
            h1 = h1->next;
            h2 = h2->next;
        }
        
        return NULL;
    }
};