//https://leetcode.com/problems/generate-parentheses/submissions/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int sz;
    void gen(vector<string>&, int, int, string);
    vector<string> generateParenthesis(int n) {
        this->sz = n;
        vector<string> ans;
        gen(ans, 0,0,"");
        return ans;
    }
    
};

void Solution::gen(vector<string>& v, int n, int m, string s)
    {
        if(n>this->sz || m>this->sz) return;
        
        if(n == this->sz)
        {
            while(m<this->sz)
            {
                s+=")";
                m++;
            }
            v.push_back(s);
        }
        
        gen(v, n+1, m, s+"(");
        if(m<n) gen(v,n,m+1,s+")");
    }

int main()
{
    Solution s;
   s.generateParenthesis(3);
}