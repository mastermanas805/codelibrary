#include<bits/stdc++.h>
using namespace std;
using namespace std;

string longestPalindromicSubstring(string s) {
  int n = s.length(), f,r, ft, rt;
	f = r = 0;
	
	for(int i=0; i<n; i++)
	{
		if(i-1 >=0 && s[i-1] == s[i])
		{
			ft = i-1;
			rt = i;
			while(ft-1 >=0 && rt+1 <n && s[ft-1] == s[rt +1])
				ft--, rt++;
			
			if(rt-ft > r-f)
				f = ft, r = rt; 
		}
		
		if(i-1 >=0 && i+1<n && s[i-1] == s[i+1])
		{
			ft = i-1;
			rt = i+1;
			
			while(ft-1 >=0 && rt+1 <n && s[ft-1] == s[rt +1])
				ft--,rt++;
			
			if(rt-ft > r-f)
				f = ft, r = rt;
		}
	}
  
  
  string x;
  for(int i=f; i<=r; i++) x+=s[i];

  return x;
}

int main()
{
    string s;
    cin>>s;
    cout<<longestPalindromicSubstring(s);
}