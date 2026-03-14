#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second

double knapsack(int n, int m, double p[], double w[])
{
	double a[n+1][m+1];

	for(int i=0; i<m+1; i++) a[0][i] = 0;

	for(int i=0; i<n+1; i++) a[i][0] = 0;

	for(int i = 1; i<n+1; i++)
	{
		for(int j = 1; j < m+1; j++)
		{
			if(j- w[i] >= 0)
			  a[i][j] = max(a[i-1][j], a[i-1][ j - (int)w[i]] + p[i]);
			else
			 a[i][j] = a[i-1][j];
		}
	}

	return a[n][m];
}

int main()
{
	int t,n,m;
	double v[1000], p[1000], profit;
	memset(v, 0, sizeof(v));
	memset(p, 0, sizeof(p));
	cin>>t;

	while(t--)
	{
		cin>>n>>m;
		profit = 0;
		for(int i=1; i<n; i++) cin>>v[i]>>p[i];

		for(int i=0; i<n; i++) p[i]/=2, profit = max(profit, knapsack(n, m, v, p)), p[i]*=2;

		cout<<profit<<endl;

		for(int i=0; i<n; i++) p[i] = v[i] = 0;
	}
}