#include<bits/stdc++.h>
using namespace std;
//https://codeforces.com/problemset/problem/479/B
int main()
{
    int n,k, mt = INT_MAX;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    vector<pair<int,int>> opr;
    while(k--)
    {
        auto maximum = max_element(a.begin(), a.end());
        auto minimum = min_element(a.begin(), a.end());

        if(*maximum - *minimum  == 1 || *maximum - *minimum == 0)
           break;
        
        opr.push_back(make_pair(maximum-a.begin() + 1, minimum-a.begin() +1));
        a[minimum-a.begin()]++;
        a[maximum-a.begin()]--;
    }

    auto maximum = max_element(a.begin(), a.end());
    auto minimum = min_element(a.begin(), a.end());

    cout<<*maximum - *minimum<<" "<<opr.size()<<endl;
    for(auto i:opr)
      cout<<i.first<<" "<<i.second<<endl;
      
}