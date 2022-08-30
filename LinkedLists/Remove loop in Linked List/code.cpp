// Remove loop in Linked List

class Solution
{
    public:
    //Function to remove a loop in the linked list.
    void removeLoop(Node* head)
    {
        if(head == NULL) return;
        
        Node *sptr, *fptr, *parent = NULL;
        sptr = head;
        fptr = head;
        
        while(fptr!=NULL && fptr->next!=NULL){
            sptr = sptr->next;
            fptr=fptr->next->next;
            if(sptr == fptr) break;
        }
        
        if(fptr==NULL || fptr->next==NULL) return;
        
        sptr = head;
        while(sptr!=fptr){
            sptr=sptr->next;
            parent = fptr;
            fptr=fptr->next;
        }
        
        if(parent != NULL)  parent->next = NULL;
        else{
            sptr = head->next;
            while(sptr != NULL && sptr->next != head) sptr=sptr->next;
            if(sptr->next != NULL)  sptr->next = NULL;
        }
    }
};