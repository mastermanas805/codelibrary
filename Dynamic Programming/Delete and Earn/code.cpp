#define mx 10001

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int f[mx];
        memset(f, 0, sizeof(f));
        
        for(auto i: nums) f[i]++;
        for(int i=0; i<mx; i++) f[i] = i*f[i];
        
        int pre, cur, temp;
        pre = cur = 0;
        
        for(int i=0; i<mx; i++)
        {
            temp = max(f[i]+pre, cur);
            pre = cur;
            cur = temp;
        }
        
        return cur;
    }
};