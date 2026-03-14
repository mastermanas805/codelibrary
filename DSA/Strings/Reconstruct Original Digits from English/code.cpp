// https://leetcode.com/problems/reconstruct-original-digits-from-english/

#include <bits/stdc++.h>

using namespace std;


class Solution {
    public:
     string originalDigits(string s) {
        
        int count[26],num[10];
        memset(count,0,sizeof(count));
        memset(num,0,sizeof(num));
        for(auto c: s) count[c-'a']++;
        
        
        
        //Unique Cases
        num[0] = count['z'-'a'];
        num[2] = count['w'-'a'];
        num[4] = count['u'-'a'];
        num[6] = count['x'-'a'];
        num[8] = count['g'-'a'];
        
        //Derived Cases
        num[1] = count['o'-'a']-num[0]-num[2]-num[4];
        num[3] = count['h'-'a']-num[8];
        num[5] = count['f'-'a']-num[4];
        num[7] = count['s'-'a']-num[6];
        num[9] = count['i'-'a']-num[5]-num[6]-num[8];
        
        string res;
        for(int i = 0; i < 10; i++) for(int j=0; j<num[i]; j++) res+=('0' + i);
        
        return res;
    }
};


int main()
{
    string s = "zeroonetwothreefourfivesixseveneightnine";
    Solution obj;
    cout<<obj.originalDigits(s);

    return 0;
}