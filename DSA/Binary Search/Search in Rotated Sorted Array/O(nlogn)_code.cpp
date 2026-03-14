/*
src = https://leetcode.com/problems/search-in-rotated-sorted-array/
hindi exp = https://youtu.be/Id-DdcWb5AU
*/

class Solution {
public:
    int sz;
    int search(vector<int>& a, int t) {
        sz = a.size();
        int ptr = FindMin(a, 0, sz-1);
        
        return max(Bsearch(a,0,ptr-1,t), Bsearch(a,ptr,sz-1,t));
        
    }
    
    int FindMin(vector<int>& a, int l, int r)
    {
        if(r>=l)
        {
            int mid = l + (r-l)/2;
            if(a[(mid+1)%sz] >= a[mid] && a[(mid+sz-1)%sz] > a[mid]) return mid;
            
            else if(a[r] < a[mid]) l = mid+1;
            
            else r = mid-1;
            
            return FindMin(a,l,r);
        }
        
        return 0;
    }
    
    int Bsearch(vector<int>& a, int l, int r, int t)
    {
        if(r>=l)
        {
            int mid = l + (r-l)/2;
            
            if(a[mid] == t) return mid;
            
            else if(a[mid]<t) l = mid+1;
            else r = mid - 1;
            
            return Bsearch(a,l,r,t);
        }
        
        return -1;
    }
};