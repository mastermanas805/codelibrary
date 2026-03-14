// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;



 // } Driver Code Ends

int a[100001];
class Solution{
  public:
    vector <int> countDistinct (int A[], int n, int k)
    {
        vector <int> v;
        memset(a, 0, sizeof(a));
        set<int> s;
        int j;
        
        for(int i=0; i<k;i++)
            {
                a[A[i]]++;
                s.insert(A[i]);
            }
        
        v.push_back(s.size());
        
        for(int i=k; i<n; i++)
        {
            j=i-k;
            a[A[i]]++;
            a[A[j]]--;
            s.insert(A[i]);
            if(a[A[j]] == 0) s.erase(A[j]);
            v.push_back(s.size());
        }
        
        return v;
    }
};

// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int n, k;
        cin >> n >> k;
        int a[n];
        for (int i = 0; i < n; i++) 
        	cin >> a[i];
        Solution obj;
        vector <int> result = obj.countDistinct(a, n, k);
        for (int i : result) 
        	cout << i << " ";
        cout << endl;
    }
    return 0;
}  // } Driver Code Ends