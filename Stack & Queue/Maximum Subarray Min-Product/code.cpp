#define mod 1000000007
class Solution {
public:
    
    
    int moduloMultiplication(int a, int b)
    {
        int res = 0; // Initialize result

        // Update a if it is more than
        // or equal to mod
        a %= mod;

        while (b)
        {
            // If b is odd, add a with result
            if (b & 1)
                res = (res + a) % mod;

            // Here we assume that doing 2*a
            // doesn't cause overflow
            a = (2 * a) % mod;

            b >>= 1; // b = b / 2
        }

        return res;
    }
    
    
    int maxSumMinProduct(vector<int>& nums) {
        nums.push_back(0);
        stack<int> s;
        int ret = 0, n = nums.size();
        int a[n], i = 0, top, x;
        a[0] = nums[i];
        for(int i=1; i<n; i++)  a[i] = (a[i-1] + nums[i]%mod)%mod;
        
        while(i<n)
        {
            if(s.empty() || nums[i] > nums[s.top()]) s.push(i++);
            
            else
            {

                top = s.top();
                s.pop();
                x = moduloMultiplication(nums[top], s.empty()? a[i-1]: ( a[i-1] - a[s.top()]) );
                ret = max(ret, x);
            }
        }
        
        return ret;
    }
};