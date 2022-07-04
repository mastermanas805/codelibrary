// https://leetcode.com/problems/arithmetic-slices
#include <bits/stdc++.h>
using namespace std;

int sets(int n)
{
    if(n < 3) return 0;
    return n*(n+1)/2 - 2*n + 1;
}

int numberOfArithmeticSlices(vector<int>& nums) {
    int x, y=2, sum = 0, n = nums.size();
    if(n < 3) return 0;

    x=nums[1]-nums[0];
    for(int i=2; i<n; i++)
    {
        if(x != nums[i]-nums[i-1]) 
        {
            sum+=sets(y);
            x = nums[i]-nums[i-1];
            y = 2;
        }
        
        else y++;
    }
    
    sum+=sets(y);
    return sum;
}

int main()
{
    vector<int> v = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    cout<<numberOfArithmeticSlices(v);

    return 0;
}
