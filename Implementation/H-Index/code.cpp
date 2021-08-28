//Mergesort concept
//https://leetcode.com/problems/h-index/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int left=0, right=citations.size()-1, n=citations.size();
        while(left<right){
            int m = left+(right-left)/2;
            int h = n-m, hCit = citations[m];
            if(h > hCit) left=m+1;
            else right=m;
        }
        if(citations[left]>=n-left) return n-left;
        if(citations[right]>=n-right) return n-right;
        return 0;
    }
    
};

int main()
{
    vector<int> v = {3,0,6,1,5};
    Solution s;
    cout<<s.hIndex(v);
}