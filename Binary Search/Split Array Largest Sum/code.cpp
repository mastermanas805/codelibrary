/*
src = https://leetcode.com/problems/split-array-largest-sum/
ref = Allocate Min No of Pages of book
*/

class Solution {
public:
    
    bool isPossible(vector<int>& w, int n, int m, int mn)
    {
        int sum = 0, days = 1;
        
        for(int i=0; i<n; i++)
        {
            if(w[i] > mn) return false;
            
            if(sum + w[i] > mn)
            {
                days++;
                sum = w[i];
                if(days > m) return false;
            }
            
            else sum+=w[i];
        }
        
        return true;
        
    }
    
    int splitArray(vector<int>& w, int d) {
        int l =0, r, weight = -1,mid, n = w.size();
        r = accumulate(w.begin(), w.end(), 0);
        
        while(l<=r)
        {
            mid = (l+r)/2;
            if(isPossible(w,n,d,mid))
            {
                weight = mid;
                r = mid - 1; 
            }
            
            else l = mid + 1;
        }
        
        return weight;
    }
};