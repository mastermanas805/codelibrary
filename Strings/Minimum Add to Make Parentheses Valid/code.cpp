// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/

class Solution {
public:
    int minAddToMakeValid(string s) {
        int cnt = 0, x = 0;
        for(auto i: s){
            if(i == '(')
                cnt++;
            else{
                if(cnt == 0){
                    x++;
                }else{
                    cnt--;
                }
            }
        }
        return cnt+x;
    }
};