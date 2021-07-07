#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> getloc(string str, string substr)
{
	vector<pair<int, int>> loc{};
	int startInd = 0;
	while( startInd < str.length() )
	 {
		 int nextInd = str.find(substr, startInd);
		 if(nextInd != string::npos)
		  {
			  loc.push_back(make_pair(nextInd, nextInd+ substr.length()) );
			  startInd = nextInd +1;
		  }
		  else
		    break;
	 }

	 return loc;
}

vector<pair<int,int>> collapse(vector<pair<int,int>> loc)
{
	vector<pair<int,int>> v;
	for(int i=0; i<loc.size();i++)
	{
		pair<int,int> p = loc[i];
		while(i<loc.size() && p.second>=loc[i].first)
			p.second = loc[i++].second;
		i--;
	  v.push_back(p);
	}
	
	return v;
}


string underscorifySubstring(string s, string substr) {
  // Write your code here.
	vector<pair<int,int>> loc = getloc(s, substr);
	loc = collapse(loc);
	string x = "";
	int start = 0;
	for(int i = 0; i< loc.size(); i++)
	{
		x += s.substr(start, loc[i].first - start);
		x+="_";
		x+= s.substr(loc[i].first, loc[i].second - loc[i].first);
		x+= "_";
		start = loc[i].second;
	}
	x+=s.substr(start, s.length() -start);
  return x;
}

int main()
{
    string s, substr;
    s = "testthis is a testtest to see if testestest it works";
    substr = "test";
    cout<<underscorifySubstring(s, substr);
}