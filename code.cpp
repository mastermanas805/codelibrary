#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> f;
        unsigned long long n=0;
        for(int i=0;i<nums.size();i++)
        {
            n = n<<1;
            n += nums[i]*1;
            f.push_back(n%5 == 0);
        }
        
                  return f;
    }
};

int main()
{
    Solution s;
    vector<int> in = {0,1,1,1,1,1};
    vector<bool> out = s.prefixesDivBy5(in);
}