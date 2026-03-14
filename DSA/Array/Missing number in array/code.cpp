// Missing number in array
#include<bits/stdc++.h>
using namespace std;

int MissingNumber(vector<int>& a, int n) {
        long x = 1 ^ a[0];
        
        for(int i=1; i<n; i++) x = x ^ a[i] ^ (i+1);
        
        return x;
    }


int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    cout<<MissingNumber(a,n)<<endl;
}