// https://leetcode.com/problems/decode-string/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string decodeString(string input) {
        string ret;
        stack<char> s;

        for(auto i: input){
            if(i == ']'){
                string str = "";
                while(s.top() != '['){
                    str += s.top();
                    s.pop();
                }
                s.pop();
                int multiplier = 0;
                string num;
                while(!s.empty() && s.top() >= '0' && s.top() <= '9'){
                    num = s.top() + num;
                    s.pop();
                }

                for(auto j: num){
                    multiplier= multiplier*10 + j - '0';
                }

                string final_str;
                for(int i=0;i<multiplier;i++) final_str+=str;

                for(int j=final_str.length()-1;j>=0;j--) 
                    s.push(final_str[j]);
                
            }else{
                s.push(i);
            }
        }

        while(!s.empty()){
            ret = s.top() + ret;
            s.pop();
        }
        return ret;
    }
};