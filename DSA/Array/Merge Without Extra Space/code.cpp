#include<bits/stdc++.h>
using namespace std;

void merge(long long a[], long long b[], int n, int m) 
{ 
    int i = 0, j = 0, k = n-1;
    while(i<=k && j<m){
        if(a[i] < b[j]) i++;
        else swap(a[k--], b[j++]);
    }
    
    sort(a, a+n);
    sort(b, b+m);
}


int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin>>n>>m;

    int a[n], b[m];

    for(int i=0; i<n; i++) cin>>a[i];

    for(int i=0; i<m; i++) cin>>b[i];

    merge(a,b,n,m);

    for(auto i: a) cout<<i<<endl;

    for(auto i: b) cout<<i<<endl;
}