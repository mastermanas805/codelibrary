#include<bits/stdc++.h>
using namespace std;

void check(string s)
{
    int l,r;
    bool visited[26];
    memset(visited, 0, sizeof(visited));
    for(int i=0;i<s.size();i++)
      if(s[i] == 'a')
        {    
            visited[0] =1;
            l = i-1;
            r = i+1;
            break;
        }
    
    if(!visited[0])
      {
          cout<<"no";
          return;
      }

    int i =1;
    while(i<26 && i<s.size())
    {
        if(visited[i])
        {
            cout<<"no";
            return;
        }

        if(l>-1 && s[l] == 'a'+i)
           {
               visited[i] =1;
               l--;
           }
        
        else if(r<26 && s[r] == 'a'+i)
         {
             visited[i] = 1;
             r++;
         }
        
        else
         {
            cout<<"no";
            return;
         }

        i++;
    }

    cout<<"yes";
}

int main()
{
    string s;
    int t;
    cin>>t;
    
    while(t--)
    {
        cin>>s;
        check(s);
        cout<<endl;
    }
}