#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
     //vector<int>par;
    int find(int x,vector<int>par)
    {
      if(par[x]==-1)
          return x;
        return find(par[x],par);
    }
    bool sim(string a,string b)
    {
        int n=a.length();
        int cnt=0;
        for(int i=0;i<n;i++)
           if(a[i]!=b[i])
               cnt++;
        if(cnt>2)
            return false;
        return true;
            
    }
    int numSimilarGroups(vector<string>& strs) {
        int n=strs.size();
         vector<int>par(n,-1);
       set<int>st;
        for(int i=0;i<n-1;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(sim(strs[i],strs[j]))
                {
                    int x=find(i,par);
                    int y=find(j,par);
                    if(x!=y)
                    par[x]=y;
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            int p=find(i,par);
            //cout<<i<<" "<<p<<endl;
            st.insert(p);
        }
        return st.size();
    }
};

int main()
{
    vector<string> in = {"tars","rats","arts","star"};
    Solution s;
    cout<<s.numSimilarGroups(in);
    return 0;
}