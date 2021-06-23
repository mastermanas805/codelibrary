#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        vector<bool> alpha(256,0);
        int longest =0;
        int front,rear;
        front = rear = 0;

        for(int i=0; i<s.size(); i++)
        {
            if(alpha[s[i]])
            {
                longest = max(longest,rear - front);
                while(s[i] != s[front])
                {
                    alpha[s[front]] = 0;
                    front++;
                }
                
                alpha[s[front]] = 0;
                front++;
            }
            rear++;
            alpha[s[i]] = 1;
        }
        
        longest = max(longest,rear - front);
        return longest;
    }
};

int main()
{
    string s = "tmmzuxt";
    Solution o;
    o.lengthOfLongestSubstring(s);
}