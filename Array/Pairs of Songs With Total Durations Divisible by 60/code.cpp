// https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int f[60];
        memset(f,0,sizeof(f));
        int cnt = 0, rem;
        for(auto i: time){
            rem = i%60;
            if(rem  == 0) cnt+=f[0];
            else{
                cnt+=f[60-i%60];
            }
            f[rem]++;
        }

        return cnt;
    }
};