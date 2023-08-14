// https://leetcode.com/problems/permutation-in-string/description/

#include<bits/stdc++.h>

class Solution {
public:

    bool check(int b[26]){
            bool f = 1;
            for(int i=0;i<26;i++)
                f&= b[i] == 0;
            return f;
        };
    bool checkInclusion(string s1, string s2) {
        if(s1.length() > s2.length())
            return 0;
            
        int b[26];
        memset(b, 0, sizeof(b));
        for(char i: s1)
            b[i-'a']++;
        
        

        int l = 0,r;
        for(r=0;r<s1.length();r++)
            b[s2[r]-'a']--;
        
        while(r-l == s1.length()  && r<s2.length()){
            if(check(b))
                return 1;

            b[s2[l]-'a']++;
            l++;
            if(r<s2.length()){
                b[s2[r]-'a']--;
            }
            r++;
        }

        if(check(b))
            return 1;

        

        return 0;
    }
};