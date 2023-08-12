// https://leetcode.com/problems/remove-k-digits/description/

class Solution {
public:
    string removeKdigits(string num, int k) {
        if(k == num.length()){
            return "0";
        }

        num+="0";

        stack<char> st;
         for(auto i:num){

            while( !st.empty() && st.top() > i && k > 0){
                st.pop();
                k--;
            }
            st.push(i);  

         }

         string s,ret;
         while(!st.empty()){
             s = st.top() + s;
             st.pop();
         }

        int i=0;
        while(s[i] == '0')
            i++;
        
        while(i<s.length()-1){
            ret+=s[i];
            i++;
        }

         return ret != ""?ret:"0";
    }
};