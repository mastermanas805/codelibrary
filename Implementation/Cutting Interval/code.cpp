//Google Kikstart
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second

void cut(vector<pair<int,int>>& intervals,pair<int,int> x, int& count)
{
    vector<pair<int,int>> temp = intervals;
    auto it = intervals.begin();
    for(auto i= temp.begin(); i != temp.end() && it != intervals.end(); i++, it++)
    {
        if( it->f < x && it->s > x)
           {
               pair<int,int> p = *it;
               intervals.erase(it);
               temp.erase(i);
               count++;
               if(x - p.f >0)
                 {
                     intervals.push_back(make_pair(p.f ,x));
                     intervals.push_back(make_pair(x, p.s));
                 }

           }
    }
}

pair<int,int> max_interval(vector<pair<int,int>>& intervals)
{
    int f = intervals[0].f ,r = intervals[0].s;

    for(int i= 0; i< intervals.size(); i++)
    {
        int f1,r1;
        f1 = intervals[i].f;
        r1 = intervals[i].s;
        i++;
        while( intervals[i].f <= r1 && i < intervals.size())
        {
            r1 = max(r1, intervals[i].s);
            i++;
        }

        if( r-f < r1-f1)
         {
             f = f1;
             r = r1;
         }
    }

    if(r-f <= 1)
      return make_pair(-1,-1);
    
    return make_pair(f,r);
}

void cal(vector<pair<int,int>>& intervals, int n, int& count)
{
    pair<int,int> x;
    while(n--)
        {
            x = max_interval(intervals);
            if(x.f == -1)
                  return;
            x.f++;
            cut(intervals,x, count);
        }
}

int main()
{
    int t,n,c,x,y,count;
    cin>>t;
    while(t--)
    {
        cin>>n>>c;
        count = n;
        vector<pair<int,int>> intervals;
        for(int i=0; i<n;i++)
         {
             cin>>x>>y;
             if(y-x > 1)
                 intervals.push_back(make_pair(x,y));
         }
        cal(intervals, n, count);
        cout<<count<<endl;
        
    }
}