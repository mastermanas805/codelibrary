//

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int hash[256] = {0};
        int thash[256] = {0};
        
        for(int i=0;i<s.length();i++){
            if(hash[s[i]] == 0 && thash[t[i]] == 0){
                hash[s[i]] = t[i];
                thash[t[i]] = 1;
            }
        }
        
        for(int i=0;i<s.length();i++){
            if(hash[s[i]] != t[i])
                return 0;
        }
        
        return 1;
    }
};