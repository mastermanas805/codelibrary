#include<bits/stdc++.h>
using namespace std;

vector<int> piTable(string s)
{
    int i = 1, len = 0, n = s.length();
    vector<int> v(n);
    v[0] = 0;
    
    while(i<n)
    {
        if(s[i] == s[len])
        {
            len++;
            v[i] = len;
            i++;
        }

        else
        {
            if(len !=0)
             len = v[len-1];

            else
            {
                v[i] = 0;
                i++;
            } 
        }
    }

    return v;
} 

bool kmp(string main, string pattern)
{
    vector<int> ppi = piTable(pattern);
    int i = 0, j = 0;

    while (i < main.length() && j<pattern.length())
    {
        if(main[i] == pattern[j])
        {
            i++;
            j++;
        }

        else
        {
            if(j != 0) j = ppi[j-1];
            else i++;
        }
    }
    
    if(j>=pattern.length()) return true;
    return false;
}

int main()
{
    string s = "ababcabcabababd", pattern = "abab";
    cout<<kmp(s, pattern);
    return 0;
}