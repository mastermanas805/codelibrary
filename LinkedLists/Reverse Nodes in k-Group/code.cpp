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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *prev = NULL, *root = head,*next = head, *x,*y;
        stack<ListNode*> s;
        int count = 0;
        while(root!=nullptr)
        {
            count= (count+1)%k;
            s.push(root);
            next = root->next;
            if(count == 0)
            {
                x = s.top();
                if(prev != NULL) prev->next = root;
                else head = x;
                s.pop();
                
                while(!s.empty())
                {
                    y = s.top();
                    s.pop();
                    x->next = y;
                    x = y;
                }
                x->next = next; 
                prev = x;
            }
            
            root = next;
        }
        
        return head;
    }
};

int main()
{
    ListNode *l = new ListNode(1);
    ListNode *x = l;
    x->next = new ListNode(2);
    x = x->next;
    x->next = new ListNode(3);
    x = x->next;
    x->next = new ListNode(4);
    x = x->next;
    x->next = new ListNode(5);
    x = x->next;
    
    Solution s;
    s.reverseKGroup(l,3);
    
    
}