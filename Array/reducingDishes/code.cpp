class Solution {
public:
    int maxSatisfaction(vector<int>& s) {
        sort(s.begin(), s.end());
        int n = s.size(), sum = 0, tsum = 0, ret;
        for(int i=0; i<n; i++)
        {
            sum+=s[i]*(i+1);
            tsum+=s[i];
        }
        
        ret = sum;
        for(int i=1; i<n && s[i]<=0; i++)
        {
            sum-=tsum;
            tsum-=s[i-1];
            ret = max(ret, sum);
        }
        
        return ret>0?ret:0;
    }
};