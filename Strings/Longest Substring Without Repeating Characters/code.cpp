class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int f[256], l = 0,h = 0, n = s.length(), mx = 1, cnt  = 0;
        if(n == 0) return 0;
        memset(f,-1,sizeof(f));
        
        while(h<n)
        {
            if(f[s[h]] < 0) f[s[h]] = h, h++, cnt++;
            else
            {
                while(l<f[s[h]]+1)
                {
                    f[s[l++]] = -1;
                    cnt--;
                }
            }
            
            mx = max(mx, cnt);
        }
        
        
        return mx;
    }
};