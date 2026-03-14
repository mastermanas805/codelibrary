#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long

class Solution {
public:
    long long colosseum(int n,vector<int> a) {
        ll s1[3*n], s2[3*n], cnt = 0, mx = INT_MIN;
       
        {
               priority_queue<int, vector<int>, greater<int> > pq;
                
                for(int i=0; i<3*n; i++)
                {
                    if(pq.size() < n) cnt+=a[i], s1[i] = cnt, pq.push(a[i]);

                    else if(pq.size() == n && a[i] > pq.top())
                        {
                            cnt = cnt - pq.top() + a[i];
                            pq.pop();
                            pq.push(a[i]);
                        }
                    s1[i] = cnt;
                }
           } 
        
        {
            priority_queue<int> pq;
            cnt = 0;

            for(int i=3*n-1; i>=0; i--)
            {
                if(pq.size() < n) cnt+=a[i], s1[i] = cnt, pq.push(a[i]);

                else if(pq.size() == n && a[i] < pq.top())
                {
                    cnt = cnt - pq.top() + a[i];
                    pq.pop();
                    pq.push(a[i]);
                }
                s2[i] = cnt;
            }
        }
        
        for (int i = n; i < 2 * n; ++i) 
            mx = max(mx, s1[i] - s2[i+1]);
        
        return mx;
        
   }
};
int main(){
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    while(T--){
        Solution obj;
        int n;
        cin>>n;
        vector<int> a(3*n);
         for (int i = 0; i <3*n; ++i){
            cin>>a[i];
        }
        cout << obj.colosseum(n,a) <<"\n";
    }
    return 0;
}
  // } Driver Code Ends