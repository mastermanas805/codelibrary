#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string removeDuplicates(string s, int k)
    {
        vector<pair<char, short>> st;
        string res;
        for (auto ch : s)
        {
            if (st.empty() || st.back().first != ch)
                st.push_back({ch, 0});
            if (++st.back().second == k)
                st.pop_back();
        }
        for (auto &p : st)
            res += string(p.second, p.first);
        return res;
    }
};

int main()
{
    string s = "deeedbbcccbdaa";
    int k = 1000;
    Solution o;
    cout << o.removeDuplicates(s, k);
}