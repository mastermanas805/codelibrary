//https://leetcode.com/problems/jump-game-ii/
#include<bits/stdc++.h>
using namespace std;

 int jump(int nums[], int n) {
        if(n < 2) return 0;
        int curr, next, level, i;
        i = level = curr = next = 0;
        
        while(curr-i >= 0)
        {
            level++;
            
            while(i<= curr)
            {
                next = max(next, nums[i]+i);
                if(next >= n-1) return level;
                i++;
            }
            
            curr = next;
        }
        
        return 0;
    }

int main()
{
    int a[] = {1,0,0};
    jump(a, sizeof(a)/sizeof(int));
}