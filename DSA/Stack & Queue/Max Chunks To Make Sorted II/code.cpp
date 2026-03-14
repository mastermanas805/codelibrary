
//src = https://leetcode.com/problems/max-chunks-to-make-sorted-ii/

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int>a(n);
        vector<int>b(n+1);
        a[0] = arr[0];
        for(int i = 1; i<n; i++)
            a[i] = max(a[i-1], arr[i]);
        
        b[n] = INT_MAX;
        for(int i = n-1; i>=0; i--)
            b[i] = min(b[i+1], arr[i]);
        
        int part = 0;
        for(int i = 0; i<a.size();i++)
            if(a[i] <= b[i+1]){
                part++;
            }
        
        return part;
    }
};

int main()
{
    vector<int> v = {5,4,3,2,1};
    Solution s;
    s.maxChunksToSorted(v);
}

