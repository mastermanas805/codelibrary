/*
https://leetcode.com/problems/find-the-closest-palindrome/
Sol - https://leetcode.com/problems/find-the-closest-palindrome/discuss/649229/C%2B%2B-Concise-and-Easy-to-Understand-with-Explanation-Faster-than-100
*/

#define pb push_back
class Solution {
public:
    string nearestPalindromic(string n) {
        if(n.length() == 1) return to_string(stoi(n)-1);
        int digits = n.length();
        vector<long> candidates;
        candidates.pb(pow(10, digits-1)-1);
        candidates.pb(pow(10, digits)+1);
        
        int mid = (digits + 1)/2;
        long prefix = stol(n.substr(0,mid));
        vector<long> v = {prefix, prefix+1, prefix-1};
        
        for(auto i:v)
        {
            string pre = to_string(i);
            if(digits%2 != 0) pre.pop_back();
            reverse(pre.begin(), pre.end());
            candidates.pb(stol( to_string(i) + pre));
        }
        
        long diff = INT_MAX, num = stol(n);
        long res;
        
        for(auto i: candidates)
        {
            if(i!=num && abs(i-num) < diff)
            {
                diff = abs(i-num);
                res = i;
            }
            
            else if(abs(i-num) == diff) res = min(res, i);
        }
        
        return to_string(res);
    }
    
    
    
};