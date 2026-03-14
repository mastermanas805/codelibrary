#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *root = NULL, *ptr = NULL, *l1 = list1, *l2 = list2;
        while(l1 != NULL && l2 != NULL){
            if(l1->val < l2->val){
                if(ptr == NULL) root = ptr = l1;
                else
                {
                    ptr->next = l1;
                    ptr = ptr->next;
                }
                l1 = l1->next;
                ptr->next = NULL;
            }else{
                if(ptr == NULL) root = ptr = l2;
                else
                {
                    ptr->next = l2;
                    ptr = ptr->next;
                }

                l2 = l2->next;
                ptr->next = NULL;
            }
        }
        
        if(l1!=NULL)
            ptr->next = l1;
        if(l2!=NULL)
            ptr->next = l2;
            
        return root;
    }
    
int main()
{
    ListNode* l1;
    l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    
    ListNode* l2;
    l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    
    mergeTwoLists(l1,l2);

    return 0;
}