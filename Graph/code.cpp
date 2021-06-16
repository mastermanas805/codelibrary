#include<bits/stdc++.h>
using namespace std;
int bk(string N, string M, string S, int s, int i)
{
    if(i>=s-1)
      return 0;
    
    if(S == N)
       return 1;
    string x;
    x+=M[i];
    int count = 0;

    count+=bk(N,M, x+M[i+1] ,s,i+1);
    count+=bk(N,M, "" ,s,i+1);
    
    if(x == "5")
        count+=bk(N,M, "2" + M[i+1] ,s,i+1);
    
    if(x == "2")
        count+=bk(N,M, "5" + M[i+1] ,s,i+1);
    
    if(x == "6")
        count+=bk(N,M, "9" + M[i+1] ,s,i+1);
    
    if(x == "9")
        count+=bk(N,M, "6" + M[i+1] ,s,i+1);
    
    return count;

}

 int main()
 {
     int s;
     string N,M;
     cin>>N>>M;
     s = M.size();
     cout<<bk(N,M,"",s,0);

 }

/*
56
245769
*/