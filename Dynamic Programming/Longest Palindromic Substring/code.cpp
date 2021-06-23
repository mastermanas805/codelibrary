#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    
    unordered_map<string, string> mp;
    string longestPalindrome(string s)
    {
        unordered_map<string, string>:: const_iterator it = mp.find(s);
        if( it != mp.end())
           return it->second;

        if(s.size() == 1)
            return s;
        
        if(s.size() == 0)
            return "";
        
        stack<char> st;
        int i;
        for(i=0; i<s.size()/2; i++)
            st.push(s[i]);
        
        i = s.size()%2? s.size()/2+1 :s.size()/2;
        for(; i<s.size(); i++)
            if(s[i] != st.top())
                break;
            else
                st.pop();
        
        if(st.empty())
            return s;
        
        string s1 = longestPalindrome(s.substr(0, s.size()-1));
        string s2 = longestPalindrome(s.substr(1, s.size()));
        
        mp[s] = s1.size() > s2.size()? s1:s2;
        return mp[s];
    }
    
};

int main()
{
    // string in = "babad";
    // string in ="abbcccbbbcaaccbababcbcabca";
    string in = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
    Solution s;
    cout<<s.longestPalindrome(in);
}