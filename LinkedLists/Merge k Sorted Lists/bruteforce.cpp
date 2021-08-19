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
        int mx = INT_MAX, sz = lists.size(), temp;
        ListNode *root = new ListNode();
        ListNode *ptr = root;
        bool flag = 1;
        while(flag)
        {
            flag = 0;
            mx = INT_MAX;
            for(int i=0; i<sz; i++)
            {
                if(lists[i] != NULL && lists[i]->val < mx)
                {
                    mx = lists[i]->val;
                    temp = i;
                    flag|=1;
                }
                
                else flag|=0;
            }
            
            if(flag)
            {
                ptr->next = new ListNode(lists[temp]->val);
                ptr = ptr->next;
                lists[temp] = lists[temp]->next;
            }
        }
        
        
        return root->next;
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