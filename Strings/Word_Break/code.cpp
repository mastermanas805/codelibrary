#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

class Solution{
public:
    vector<string> wordBreak(int n, vector<string>& dict, string s)
    {
        vector< pair<int,int> > v;
        vector<string> ret;
        
        for(auto i: dict){
            int index = 0;
            while ((index = s.find(i, index)) != std::string::npos)
                v.pb( mp(index, i.length() ) );
        }
        
        sort(v.begin(), v.end());
        
        for(auto i: v){
            string x = s.substr(i.first, i.second);
            ret.push_back(x);
        }
        
        return ret;
    }
};


int main(){
    // freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n = 5;
    string s = "catsanddog";
    vector<string> dict;
    string c[] = {"cats", "cat", "and", "sand", "dog"};
    vector<string> dest(begin(c), end(c));
    Solution obj;
    for(auto i:obj.wordBreak(n, dict, s)) 
        cout<<i<<endl;
    return 0;
}