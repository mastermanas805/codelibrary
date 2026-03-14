#include <vector>
using namespace std;

int numberOfWaysToMakeChange(int n, vector<int> denoms) {
  // Write your code here
	int a[n+1];
	memset(a,0,sizeof(a));
	a[0] = 1;
	for(int denom: denoms)
		for(int i=1;i<n+1;i++)
			if(denom <= i)
				a[i]+= a[i-denom];
  return a[n];
}
