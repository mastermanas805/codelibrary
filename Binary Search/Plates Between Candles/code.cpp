//https://leetcode.com/problems/plates-between-candles/
class Solution {
public:
    int closestleft(int a[], int n, int x){
        int l = 0, r = n-1, mid, ans = -1;
        while(l<=r){
            mid = (l + r)/2;
            if(a[mid] >= x) ans = mid, r = mid - 1;
            else l = mid + 1;

        }
        return ans;
    }


    int closestright(int a[], int n, int x){
        int l = 0, r = n-1, mid, ans = -1;
        while(l<=r){
            mid = (l + r)/2;
            if(a[mid] <= x) ans = mid, l = mid +1;
            else r = mid - 1;
        }
        return ans;
    }

    int solve(vector<int> q, int a[], int n){
        int  l = closestleft(a,n,q[0]), r = closestright(a,n,q[1]), candles;
        if(l == -1 || r == -1) return 0;
        candles = r-l-1;
        int ans = a[r] - a[l] - 1 - candles;
        return ans > 0? ans:0;
    }
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.length(), a[n], j=0;
        for(int i=0; i<n; i++)
                if(s[i] == '|') a[j++] = i;
        vector<int> v;
        for(auto i: queries)
            v.emplace_back(solve(i,a,j));
        return v;
    }
};