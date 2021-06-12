#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ans;
        int num;
        
        ans.push_back(0);
        ans.push_back(1);
        
        for(int i=2;i<=n;i++)
        {
            num=1<<(i-1);
           for(int j=ans.size()-1;j>=0;j--)
               {
                   ans.push_back(num+ans[j]);
               }
        }
        
        return ans;
    }
};

int main()
{
    int n;
    cout<<"Enter the N : ";
    cin>>n;
    Solution s;
    vector<int> ans = s.grayCode(n);
    cout<<endl<<"{"<<" ";
    for(auto &i: ans)
     cout<<i<<", ";
    
    cout<<" }"<<endl;

}