// https://leetcode.com/problems/maximum-units-on-a-truck/

bool comp(vector<int> a, vector<int> b){
        return a[1] > b[1];
    }

class Solution {
public:
    
    int maximumUnits(vector<vector<int>>& boxTypes, int sz) {
        sort(boxTypes.begin(), boxTypes.end(), comp);
        int cnt = 0;
        for(auto i: boxTypes){
            if(sz <= 0) break;
            if(i[0] >= sz) cnt+= sz*i[1],sz = 0;
            else cnt+= i[0]*i[1], sz-=i[0];
        }
        
        return cnt;
    }
};