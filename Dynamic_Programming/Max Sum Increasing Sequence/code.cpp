#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> maxSumIncreasingSubsequence(vector<int> a) {
  
	int  n = a.size(), maxSum = 0;
	vector<int> sum = a,seq(n,-1);
	
	
	for(int i=0;i<n;i++)
	{
		for(int j=0; j<i; j++ )
		{
			if(a[i] > a[j] && sum[i] <= a[i] + sum[j])
				sum[i] = sum[j]+ a[i], seq[i] = j;
		}
		
		if(sum[maxSum] <= sum[i])
			maxSum = i;
	}
	
	vector<int> v;
	int i = maxSum;
	while(seq[i] != -1)
		v.push_back(a[i]), i = seq[i];
	v.push_back(a[i]);
	reverse(v.begin(), v.end());
	
  return {
		{sum[maxSum]}, // Sum of sequence.
      v  // Elements of the sequence.
  };
}



int main()
{
    vector<int> a = {10, 70, 20, 30, 50, 11, 30};
    maxSumIncreasingSubsequence(a);
}