//https://leetcode.com/problems/merge-k-sorted-lists/
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0);
        ListNode* result;
        result = &dummy;
        
        priority_queue<int, std::vector<int>, std::greater<int> >myQ;

        for(auto l : lists){
            while(l){
                myQ.push(l->val);
                l = l->next;
            }
        }
        
        while(!myQ.empty()){
            ListNode* val = new ListNode(myQ.top());
            result->next = val;
            result = result->next;
            myQ.pop();
        }
        return dummy.next;
    }
};

int main()
{
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);
    
    ListNode *l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    
    ListNode *l3 = new ListNode(2);
    l3->next = new ListNode(6);
    
    Solution s;
    vector<ListNode*> v = {l1,l2,l3};
    s.mergeKLists(v);
    
}