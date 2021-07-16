#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>::iterator max_element(vector<pair<int,int>>& v)
{
    vector<pair<int,int>>::iterator it,m;
    m = it = v.begin();
    while(it != v.end())
      if(it->second - it->first > m->second - m->first)
        m = it;
    return m;
}

void merge(vector<pair<int,int>>& v)
{
    for(int i = 0; i < v.size() - 1; i++)
    {
        int x = v[i].second;
        while(x>=v[i+1].first)
           {
               x = v[i+1].second;
               i++;
           }
        i--;
    }
}
int main()
{
    int t,n,a,b, score,f,e;
    bool x;
    string s;
    cin>>t;
    while(t--)
    {
        cin>>n>>a>>b>>s;
        vector<pair<int,int>> one,zero;
        score=0;
        f = 0;

        for(int i=1;i<n;i++)
        {
            if(s[i] != s[f])
             {
                if(s[f] == '1')
                    one.push_back(make_pair(f,i-1));
                else
                    zero.push_back(make_pair(f,i-1));
                f =i;
             }
        }

        if(s[f] == '1')
            one.push_back(make_pair(f,n-1));
        else
            zero.push_back(make_pair(f,n-1));
        
        while(!one.empty() || !zero.empty())
        {
            bool type;
            vector<pair<int,int>>::iterator it, i;
            if(!zero.empty())
              {
                  type = 0;
                  it = max_element(zero);
              }
            
            if(!one.empty())
              {
                  type = 1;
                  it = max_element(one);
              }
            score+=a*(it->second - it->first) + b;
            if(type == 0)
             { 
                 i = it+1;
                 while(i != zero.end())
                  {
                      i->first-=it->second;
                      i->second-=it->second;
                      i++;
                  }
                zero.erase(it);
             }
            
        }
    }

}