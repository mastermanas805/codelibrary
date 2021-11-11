/*
src = https://leetcode.com/problems/coin-change/
exp = https://youtu.be/I-l6PBeERuc
*/
#include <bits/stdc++.h>
using namespace std;

#define mx 10e4 + 1
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        int t[n+1][amount+1];
        
        for(int i=0; i<amount+1; i++)        t[0][i] = mx;
        for(int i=1; i<n + 1; i++) t[i][0] = 0;
        
        for(int i=1; i<amount + 1; i++)
        {
            if(i%coins[0]) t[1][i] = mx;
            else t[1][i] = i/coins[0];
        }
        
        for(int i=2; i<n+1; i++)
        {
            for(int j=1; j<amount+1; j++)
            {
                if(coins[i-1] <= j)
                    t[i][j] = min(t[i-1][j], 1 + t[i][j - coins[i-1]]);
                else
                    t[i][j] = t[i-1][j];
            }
        }
        
        return t[n][amount] == mx? -1: t[n][amount];
    }
};

int main()
{
    vector<int> v = {2};
    int target = 3;
    Solution s;
    s.coinChange(v,target);

    return 0;
}
