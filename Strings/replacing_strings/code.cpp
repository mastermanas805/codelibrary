/*
Replace all occurrences of a substring in original string by replacement_string.
	Example: 
Original_string =“johnmarkmmarkpeter”, target_substring =  “mark”,replacement_string =”fictional” , result = “johnficitonalmfictionalpeter”
*/

#include<bits/stdc++.h>
using namespace std;
string replace_with_target(string s, string t,string rs, int i)
{
    string ret = s;
 //+
  int x = t.length(), y = rs.length();
  if(t.length() < rs.length())
  {
      // means create more space as replacing string is of more length
      int n = s.length();
      // shifting chars to create extra space towards right
      for(int a = s.length()- (rs.length() - t.length()); a<n; a++)
       ret+=ret[a];
      // shifting chars to new position
      for(int a = 0 , b = (rs.length() - t.length()); a< (rs.length() - t.length()); a++)
         ret[a+b + i+1] = s[a + i + 1];
      
      //replacing the strings
      i = i - t.length() + 1;
      for(int a = 0; a<rs.length(); a++) ret[a+i] = rs[a];

  }

  else if(t.length() > rs.length())
  {
      //means shrink of space
      int j = i - (t.length() - 1), a, y =  (t.length() - rs.length());
      //replacing the strings
      for(a = 0; a<rs.length(); a++)
        ret[a+j] = rs[a];
      // shifting chars towards left
      for(j= i+1; j<s.length(); j++)
        ret[j-y] = ret[j];
      // marking empty space with +
      for(j = ret.length() - y; j<ret.length(); j++)
        ret[j] = '+';

      
  }

  else
  {
      //replacing strings
      i = i - (t.length() - 1);
      for(int a = 0; a<rs.length(); a++)
       {
           ret[a+i] = rs[a];
       }
  }
  return ret;
}

string replace(string s, string t, string rs)
{
    int n = s.length();
    int j =0;
    for( int i =0; i<n && s[i] != '+'; i++)
    {
        if(s[i] == t[j]) j++;

        else 
         {
             if(s[i] == t[0]) j = 1;

             else j = 0;
         }

        if(j == t.length()) 
        {
            s = replace_with_target(s,t,rs,i);
            return replace(s,t,rs);
        }
    }

    return s;
}


int main()
{
    string s = "johnmarkmmarkpeter", target_substring = "mark", replacement_string = "fictional";
    string res = replace(s, target_substring, replacement_string);

    for(int i=0; i<res.length() && res[i] != '+'; i++)
       cout<<res[i];

}