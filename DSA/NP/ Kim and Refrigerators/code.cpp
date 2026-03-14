#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second

pair<int,int> p[15];
bool visited[15];
int ans, n;

int distance(pair<int,int> a, pair<int,int> b){
    return abs(a.ff-b.ff)+abs(a.ss-b.ss);
}

void explore(pair<int,int> current, int cost, int nodeleft){
    if(nodeleft == 0){
        cost+=distance(current, p[1]);
        ans = min(cost, ans);
        return;
    }
    
    for(int i=2; i<n+2; i++){
        if(!visited[i]){
            visited[i] = 1;
            explore(p[i], cost + distance(current, p[i]), nodeleft-1);
            visited[i] = 0;
        }
    }
}

int main() {
    for(int i=0; i<10; i++){
        ans = INT_MAX;
        memset(p, false, sizeof(p));
        cin>>n;
        for(int i=0; i<n+2; i++) cin>>p[i].ff>>p[i].ss;
        explore(p[0], 0, n);
        
        cout<<"# "<<i+1<<" "<<ans<<endl;
        
    }
    return 0;
}
