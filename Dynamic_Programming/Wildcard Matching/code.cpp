/* *************************** Recurtsion ******************************************** */
class Solution {
public:
    string s,p;
    vector<vector<int>> dp;
    bool isMatch(string s, string p) {
        this->s = s;
        this->p = p;
        dp.resize(s.length()+1, vector<int>(p.length()+1,-1));

        return ismatch(s.length(), p.length());
    }

    bool ismatch(int i, int j){
        if(i == 0 && j == 0) return 1;
        if(i == 0) return p[j-1] == '*' && ismatch(i, j-1);
        if(j == 0) return 0;

        if(dp[i][j] >-1) return dp[i][j];

        if(p[j-1] == '?')  return dp[i][j] = ismatch(i-1, j-1);

        if(p[j-1] == '*') return dp[i][j] = ismatch(i-1,j) || ismatch(i,j-1);

        return dp[i][j] =  s[i-1] == p[j-1] && ismatch(i-1, j-1);
    }


};
/* *************************** Iterative ******************************************** */

class Solution {
public:
    string s,p;
    vector<vector<bool>> dp;
    bool isMatch(string s, string p) {
        this->s = s;
        this->p = p;
        dp.resize(s.length()+1, vector<bool>(p.length()+1,0));

        dp[0][0] = 1;

        for(int i=0;i<=s.length();i++){
            for(int j=1;j<=p.length();j++){
                if (i == 0)
                    dp[i][j] = p[j-1] == '*' && dp[i][j-1];
                else if(p[j-1] == '?') 
                    dp[i][j] = dp[i-1][j-1];
                else if(p[j-1] == '*')
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                else
                    dp[i][j] = s[i-1] == p[j-1] && dp[i-1][j-1];
            }
        }

        return dp[s.length()][p.length()];
    }


};