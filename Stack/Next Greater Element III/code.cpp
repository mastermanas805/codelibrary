/*
src - https://leetcode.com/problems/next-greater-element-iii/
reference - (Next Permutation) https://github.com/mastermanas805/codelibrary/blob/master/Array/Next%20Permutation/code.cpp
hindi explanation - https://www.youtube.com/watch?v=LuLCLgMElus
*/

#define pb push_back
class Solution {
public:
    int arrtoint(vector<int> v)
    {
        long long int n = 0;
        for(auto i: v)   n = n*10 + i;
        return (n<0 || n>INT_MAX)?-1:n;
    }
    
    int nextGreaterElement(int n) {
        
        int sz = log10(n)+1,i = sz-2,j;
        queue<int> q;
        vector<int> a;
        a.reserve(sz);
        while(n>0) a.pb(n%10), n/=10;
        reverse(a.begin(),a.end());
        
        for(i = sz-2; i>=0; i--)
            if(a[i+1] > a[i]) break;
        
        if(i<0) return -1;
        
        else
            {
                    for(j = sz-1; j>i;j--)
                        if(a[j] > a[i]) break;
                swap(a[i],a[j]);
                reverse(a.begin()+i+1, a.end());
                return arrtoint(a);
           }
    }
};