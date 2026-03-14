// https://leetcode.com/problems/decode-ways/

class Solution {
public:
    int numDecodings(string s) {
        int n = s.length(), a[n+1], first, second;
        
        if(s[0] == '0') return 0;
        else if(n<2) return 1;
        
        memset(a,0, sizeof(a));
        a[0] = 1;
        a[1] = 1;
        
        for(int i=2;i<=n;i++)
        {
            first = s[i-1]-'0';
            second = (s[i-2]-'0')*10 + s[i-1] - '0';
            if(first > 0) a[i]+=a[i-1];
            if(second >= 10 && second<=26) a[i]+=a[i-2];
        }
        
        return a[n];
    }
};