// CPP program to find all subsets by backtracking.
#include <bits/stdc++.h>
using namespace std;
#define ll long
#define mx 1000000007
void subsetsUtil(vector<ll>& A,
				vector<ll>& subset, ll index, ll& sum, ll sand)
{
	if(index == 0) sand = A[0];
	else 
	  sum = (sum%mx + sand%mx)%mx;
	
	for (ll i = index; i < A.size(); i++) {

		// include the A[i] in subset.
		subset.push_back(A[i]);

		// move onto the next element.
		subsetsUtil(A, subset, i + 1, sum, sand&A[index]);

		// exclude the A[i] from subset and triggers
		// backtracking.
		subset.pop_back();
	}

	return;
}

// below function returns the subsets of vector A.
ll subsets(vector<ll>& A)
{
	vector<ll> subset;
	ll sum = 0,sand;

	// keeps track of current element in vector A;
	ll index = 0;
	subsetsUtil(A, subset, index, sum, 0);
    for(int i=1; i<A.size(); i++)
      sum = (sum%mx + A[i]%mx)%mx;

	return sum;
}

// Driver Code.
int main()
{
	// find the subsets of below vector.
	int t,n;
	cin>>t;

	while(t--)
	{
        cin>>n;
		vector<ll> a(n);
		for(int i=0; i<n; i++)
		  cin>>a[i];

		cout<<subsets(a)<<endl;
	}

	return 0;
}
