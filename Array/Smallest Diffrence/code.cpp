#include<bits/stdc++.h>
using namespace std;

int getclosest(int a, int b, int t)
{
    return abs(t-a)<abs(t-b)? a:b;
}

int closest(vector<int> a, int t)
{
    int n = a.size();
    if(t<=a[0])
       return a[0];
    
    if(t>=a[n-1])
        return a[n-1];
    
    int l,h,m;
    l = 0;
    h = n-1;

    while(l<h)
    {
        m = (l+h)/2;
        if(a[m] == t)
          return a[m];

        if(t < a[m])
          {
              if(m > 0 && a[m-1] < t)
                return getclosest(a[m], a[m-1], t);
              h = m;
          }
        
        else
         {
             if(m < n-1 && a[m+1] > t)
               return getclosest(a[m], a[m+1], t);
            
            l = m+1;
         }

    }

    return a[m];
}

vector<int> smallestDifference(vector<int> arrayOne, vector<int> arrayTwo) {
  sort(arrayOne.begin(), arrayOne.end());
  sort(arrayTwo.begin(), arrayTwo.end());

  vector<int> p = {arrayOne[0], arrayTwo[0]};
	
	for(auto i: arrayOne)
	{
		int x = closest(arrayTwo, i);
		if(abs(p[0] - p[1]) > abs(i - x))
		{
			p[0] = i;
			p[1] = x;
		}
	}
  return p;
}

int main()
{
    vector<int> a = {-1, 5, 10, 20, 28, 3}, b = {26, 134, 135, 15, 17};
    smallestDifference(a,b);
}
