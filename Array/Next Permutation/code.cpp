#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    void nextPermutation(vector<int>& a) {
        int sz = a.size(),i = sz-2,j;
        for(i = sz-2; i>=0; i--)
            if(a[i+1] > a[i]) break;
        
        if(i<0) reverse(a.begin(), a.end());
        
        else
        {
                for(j = sz-1; j>i;j--)
                    if(a[j] > a[i]) break;
            swap(a[i],a[j]);
            reverse(a.begin()+i+1, a.end());
       }
    }

    void swap(int &a, int &b)
    {
        a+=b,
        b = a- b,
        a = a - b;
    }
};

int main()
{
    vector<int> v = {3,2,1};
    Solution s;
    s.nextPermutation(v);
}