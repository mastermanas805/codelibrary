//https://codeforces.com/problemset/problem/475/B
//B. Strongly Connected City
//Author: Ke Li <
//Date: 2015-07-01
#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>>& adj, int x)
{
    int temp, count;
    for(int i=0; i<x;i++)
    {
        stack<int> s;
        count = 0;
        vector<bool> visited(adj.size(), false);
        s.push(i);
        visited[i] = true;
        while(!s.empty())
        {
            
            temp = s.top();
            s.pop();
            count++;
            for(auto i: adj[temp])
            {
                if(!visited[i])    
                    s.push(i), visited[i] = true;;
            }
        }

        if(count != x)
         {
             cout<<"NO"<<endl;
             return;
         }
    }

    cout<<"YES"<<endl;
}

int main() 
{
    int n,m;
    cin>>n>>m;
    vector<char> col(n), row(m);
    vector<vector<int>> adj(m*n);
    int x,y;

    for(int i = 0; i < n; i++) cin>>col[i];
    for(int i = 0; i < m; i++) cin>>row[i];
    
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < m; j++)
         {
             if(col[i] == '<')
                {

                    x = i;
                    y = j;
                    while(--y>=0)
                        adj[i*m+j].push_back(x*m+y);
                }

                else if(col[i] == '>')
                    {

                        x = i;
                        y = j;
                        while(++y<m)
                            adj[i*m+j].push_back(x*m+y);
                    }

                if(row[j] == '^')
                {

                    x = i;
                    y = j;
                    while(--x>=0)
                        adj[i*m+j].push_back(x*m+y);
                }

                else if(row[j] == 'v')
                {

                    x = i;
                    y = j;
                    while(++x<n)
                        adj[i*m+j].push_back(x*m+y);
                } 
         }

         dfs(adj, n*m);
}