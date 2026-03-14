#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int arr[101];
    int minsum[10001];
    Solution()
    {
        memset(minsum, 0, sizeof(minsum));
        for(int i=1;i<101;i++)
             arr[i] = i*i;
    }
    
    int numSquares(int n) {
        
        if(n<0)
            return INT_MAX;
        
        if(n == 0)
            return 0;
        
        if(minsum[n] > 0)
          return minsum[n];
        
        int count = INT_MAX;
        int i=1;
        while(arr[i] <=n && i<101)
            count = min(count, numSquares(n - arr[i++]) + 1);
        
        return minsum[n] = count;
    }
};

int main()
{
    int n = 12;
    Solution s;
    cout<<s.numSquares(n);
}