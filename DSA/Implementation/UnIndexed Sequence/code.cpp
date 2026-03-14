#include<bits/stdc++.h>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,x,count=0;
    cin>>n;
    for(int i=0;i<n; i++)
    {
        cin>>x;
        if(x == i+1) count++;
    }


    if(count == 0) cout<<0;

    else if(count > 1)
    {
        if(count%2 == 0) cout<<count/2;
        else cout<<count/2+1;
    }
    else cout<<1;
    return 0;
}