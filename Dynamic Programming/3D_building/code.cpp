/*
You are in a 3D World where there are many buildings. You can consider the buildings 
as heights given in a 2D matrix. For example: [[2,3], [1,4]] means at 0,0 there is 
building of height 2 and so on. You start at any building in first row. You can jump 
from buildings by using a energy equal to height difference. 

For example if building height is 2 and you jump from there to a building of height 
            4 you use |4-2| units of energy that is 2 units. 

Minimum energy needed to reach any building in the last row

Only valid moves are in next buildings in 4 directions (up, left, down, right)

Solve this problem, write your approach in a doc along with code. Code should be 
well written as well
*/

#include<bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define mx 1000000
using namespace std;

//calculate minimum energy stage wise
int min_energy(vector<vector<int>> v, pair<int,int> n, vector<int> visited, int i)
{
    //if i pointer is succeding the second last stage
    if(i >= n.ff - 1) return 0;

    //if the stage is already computed
    if(visited[i] != -1) return visited[i];

    int mn = mx;
    for(int j=0;j<n.ss; j++)
          mn = min(mn,abs(v[i][j] - v[i+1][j]) + min_energy(v,n,visited,i+1) );
    
    //storing and returning the minimum value
    return visited[i] = mn;
}

int main()
{
    int x,y;
    pair<int,int> n;
    cout<<"Enter no of rows"<<"\t";
    cin>>n.ff;
    cout<<"Enter no of buildings per rows"<<"\t";
    cin>>n.ss;
    cout<<"Enter Height of buildings \n";

    if(n.ff < 2) { cout<<0; return 0;}

    vector<vector<int>> v(n.ff);
    vector<int> visited(n.ff, -1);

    for(int i=0;i<n.ff; i++)
    {
      for(int j=0; j<n.ss; j++)
       {
           cin>>x;
           v[i].pb(x);
       }
    }

    int mn = mx;
    for(int i=0; i<n.ss; i++)
      mn = min(mn, abs(v[0][i] - v[1][i]) + min_energy(v,n,visited,1));
    
    cout<<"Minimum Energy Required:  "<<mn;
    return 0;

}