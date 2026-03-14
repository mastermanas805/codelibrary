//  https://leetcode.com/problems/powx-n/
class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        long long nn = n;
        if(nn < 0) nn*=-1;
        while(nn)
        {
            if(nn%2)
            {
                ans*=x;
                nn-=1;
            }
            
            else
            {
                x*=x;
                nn/=2;
            }
        }
        
        return n>0?ans: 1/ans;
    }
};