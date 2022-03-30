//https://leetcode.com/problems/reverse-nodes-in-k-group/
#include<bits/stdc++.h>
using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 

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
    
    ListNode* reverseEvenLengthGroups(ListNode* head) {
         
        
        ListNode *sptr, *fptr, *front = NULL, *nxt;
        int count, i = 1;
        sptr = fptr = head;
        
        while(fptr != NULL)
        {
            if(i%2 == 0)
            {
                count=1;
                fptr = sptr;
                while(count<i)
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
            
            else
            {
                count = 0;
                while(fptr != NULL && count < i)
                {
                    front = fptr;
                    fptr = fptr->next;
                    count++;
                }
                if(fptr == NULL) return head;
                sptr = fptr;
            }
            i++;
        }
        
        return head;
    }
};



int main()
{
    ListNode *head = new ListNode(1), *ptr;
    ptr = head;
    for(int i=2; i<6; i++) 
    {
        ptr->next =  new ListNode(i);
        ptr = ptr->next;
    }

    Solution s;
    head =  s.reverseEvenLengthGroups(head);

    while(head!=NULL) 
    {
        cout<<head->val<<"->";
        head = head->next;
    }
}