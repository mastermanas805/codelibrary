class Solution {
public:
    bool searchMatrix(vector<vector<int>>& a, int t) {
        int m = a.size(), n = a[0].size();
        int l = 0, r = m*n-1, mid;
        while(l<=r)
        {
            mid = l + (r - l)/2;
            if(a[mid/n][mid%n] == t) return 1;
            
            if(a[mid/n][mid%n] > t) r=mid-1;
            else l = mid+1;
        }
        
        return 0;
    }
};