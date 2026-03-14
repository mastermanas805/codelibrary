#define pb push_back
#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj(10000);
int pred[10000], dist[10000];

int getVal(int a, int b, int c, int d)
{
    return a*1000+b*100+c*10+d;
}

void setVal(int a, int b, int c, int d)
{
    
    adj[getVal(a,b,c,d)].pb(getVal((a-1+10)%10,b,c,d));
    adj[getVal(a,b,c,d)].pb(getVal((a+1)%10,b,c,d));
    
    adj[getVal(a,b,c,d)].pb(getVal(a,(b-1+10)%10,c,d));
    adj[getVal(a,b,c,d)].pb(getVal(a,(b+1)%10,c,d));
    
    adj[getVal(a,b,c,d)].pb(getVal(a,b, (c-1+10)%10,d));
    adj[getVal(a,b,c,d)].pb(getVal(a,b, (c+1)%10,d));
    
    adj[getVal(a,b,c,d)].pb(getVal(a,b, c, (d-1+10)%10));
    adj[getVal(a,b,c,d)].pb(getVal(a,b, c, (d+1)%10));
    
}


void pre()
{
    memset(dist,INT_MAX,sizeof(dist));
    memset(pred, -1, sizeof(pred));
    for(int a = 0; a<10; a++)
        for(int b = 0; b<10; b++)
            for(int c = 0; c<10; c++)
                for(int d = 0; d<10; d++)
                    setVal(a,b,c,d);
}


bool BFS(int src, int dest, int v,
         int pred[], int dist[], int dead[], int d)
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        
        if(find(dead, dead+d, i) != dead+d)
        {    
            visited[i] = true;
            if(i == 0)
                return -1;
        }
        else
            visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        int count = 0, t = getVal(target[0]-'0', target[1]-'0', target[2]-'0', target[3]-'0'); 
        
        if(!t) return 0;
        
        int dead[deadends.size()], j = 0;
        for(auto i: deadends)
        {
            dead[j] = getVal(i[0]-'0', i[1]-'0', i[2]-'0', i[3]-'0');
            if(dead[j] == 0) return -1;
            j++;
        }
        
        sort(dead, dead + deadends.size());
        pre();
        
        if(!BFS(0, t, 10000, pred, dist, dead, deadends.size()))
            return -1;
        
        return dist[t];
    }
};