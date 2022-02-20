/*
'(, [, {'
'(, [, {'
'()[]'

*/

#include<bits/stdc++.h>
using namespace std;

bool sol(string s)
{
    stack<char> st;
    int i = 0, n = s.length();
    while(i < n)
    {
        if(st.empty() && (s[i] == ')' || s[i] == ']' || s[i] == '}')) return 0;

        if(s[i] == ')' && st.top() == '(') st.pop();
        else if(s[i] == ']' && st.top() == '[') st.pop();
        else if(s[i] == '}' && st.top() == '{') st.pop();
        else if(s[i] == '(' || s[i] == '[' || s[i] == '{') st.push(s[i]);
        else return 0;
        i++;
    }

    if(!st.empty()) return 0;
    return true;
}

int main()
{
    string s;
    cin>>s;

    if(sol(s)) cout<<"Balanced";
    else cout<<"Unbalanced";

}