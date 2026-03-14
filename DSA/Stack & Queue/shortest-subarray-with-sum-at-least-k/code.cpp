#include<bits/stdc++.h>
using namespace std;

int shortestSubarray(vector<int> A, int K) {        int N = A.size(), res = N + 1,x;
        deque<int> d;
        vector<long> B(N+1);
        B[0] = 0;
        for(long i=1;i<N+1; i++) B[i] = B[i-1] + A[i-1];

        for(long i=0;i<N+1;i++)
        {
            while(d.size()>0 && B[i] <= B[d.back()]) d.pop_back();

            while(d.size()>0 && B[i] - B[d.front()] >= K)
            {
                x = i - d.front();
                res = min(res, x);
                d.pop_front();
            }

            d.push_back(i);
        }

        return res <= N ? res : -1;
    }

int main()
{
    vector<int> v = {2,-1,2};
    int target = 3;
    cout<<shortestSubarray(v,target);
}