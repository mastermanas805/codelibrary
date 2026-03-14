//https://leetcode.com/problems/integer-replacement/
#include<bits/stdc++.h>
using namespace std;
class Solution 
{
    
public:

    /*

    All you need is determine replace n with n + 1 or n - 1, when n is odd. since,

    if n is even, you get no choice, just replace it with n / 2.
    if n is odd, you can either add 1 or reduce 1.

    If n + 1 % 4 == 0, replace n with n + 1 will short the path. Otherwise, replace n with n - 1 is always the right direction.
    */
    int integerReplacement(int n) 
    {
        if (n == 1)
            return 0;
        

        if (n == INT_MAX)
            return 32;
        int res = 0;
        
        while(n != 1)
        {
            if (n == 3) { res+=2; break; }
                
            if (n & 1)
                if ((n + 1) % 4 == 0)
                    n+=1;
                else
                    n-=1;
            else
                n/=2;
            
            res ++;
        }
        
            
        return res;
    }
};

int main()
{
    Solution s;
    cout<<s.integerReplacement(8);
}