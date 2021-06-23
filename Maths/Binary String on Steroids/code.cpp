#include<bits/stdc++.h>
using namespace std;

signed main ()
{
//      freopen("input.txt", "r", stdin);
  int t;
  cin >> t;
  while (t--)
    {
      int n;
      cin >> n;
      string s;
      cin >> s;
      int sum = 0;
      for (int i = 0; i < n; i++)
	sum += s[i] - '0';

      int ans = n;

      for (int x = 1; x <= n; x++)
	{
	  if(n % x)
	    continue;

	  for (int j = 0; j < x; j++)
	    {
	      int temp = 0;
	      for (int k = j; k < n; k += x)
		{
		  if (s[k] == '1')
		    temp -= 1;
		  else
		    temp += 1;
		}

	      ans = min (ans, sum + temp);
	    }

	}
      cout << ans << endl;
    }


  return 0;
}
