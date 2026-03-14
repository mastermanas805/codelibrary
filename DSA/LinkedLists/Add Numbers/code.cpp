//https://leetcode.com/problems/add-two-numbers/

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<ListNode*> s1,s2;
        ListNode *root = new ListNode(),*temp;
        int x;
        while(l1 != NULL) {s1.push(l1); l1 = l1->next;}
        while(l2 != NULL) {s2.push(l2); l2 = l2->next;}
        x = 0;
        if(!s1.empty()) {x+=s1.top()->val,s1.pop();}
        if(!s2.empty()) {x+=s2.top()->val,s2.pop();}
       
        root->val = x%10;
        x/=10;
        temp = root;
        while(!s1.empty() && !s2.empty())
        {
            x+=s1.top()->val+s2.top()->val;
            s1.pop();
            s2.pop();
            temp->next = new ListNode(x%10);
            x/=10;
            temp = temp->next;
        }
        
        
        while(!s1.empty())
        {
            x+=s1.top()->val;
            s1.pop();
            temp->next = new ListNode(x%10);
            x/=10;
            temp = temp->next;
        }
        
        while(!s2.empty())
        {
            x+=s2.top()->val;
            s2.pop();
            temp->next = new ListNode(x%10);
            x/=10;
            temp = temp->next;
        }
        
        
        return root;
    }
};
int main()
{
    ListNode* l1 = new ListNode(2);
    l1->next  = new ListNode(4);
    l1->next->next = new ListNode(3);
    l1->next->next->next = new ListNode();
    
    ListNode* l2 = new ListNode(5);
    l2->next  = new ListNode(6);
    l2->next->next = new ListNode(4);
    l2->next->next->next = new ListNode();
    
    Solution s;
    s.addTwoNumbers(l1,l2);
}