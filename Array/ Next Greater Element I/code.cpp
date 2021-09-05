//source
//https://leetcode.com/problems/next-greater-element-i/
/* ------------------------------------------------------------------------ */
//refrence
//https://www.youtube.com/watch?v=NXOOYYwpbg4&list=PL_z_8CaSLPWdeOezg68SKkeLN4-T_jNHd&index=3
//https://www.geeksforgeeks.org/next-greater-element/

 #define pb push_back
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size(), m = nums2.size();
        stack<int> s;
        vector<int> ans,temp;
        int i = n-1, j = m-1;
        
        while(j>=0)
        {
            while(!s.empty() && s.top()<=nums2[j]) s.pop();
           
           if(s.empty()) temp.pb(-1);
           else temp.pb(s.top());
           
           s.push(nums2[j]);
           j--;
        }
        
        reverse(temp.begin(), temp.end());
        
        for(i=0; i<n;i++)
        {
            vector<int>::iterator ptr = find(nums2.begin(), nums2.end(), nums1[i]);
            ans.pb(temp[ptr - nums2.begin()]);
        }
        return ans;
    }
};