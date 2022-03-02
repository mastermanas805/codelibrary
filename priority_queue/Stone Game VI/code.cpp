#include<bits/stdc++.h>
#define mp make_pair
#define ff first
#define ss second
using namespace std;

class Solution {
public:
    int stoneGameVI(vector<int> aliceValues, vector<int> bobValues) {
        priority_queue<pair<int, int>> a,b;
        for(int i=0; i<aliceValues.size(); i++)
            a.push(mp(aliceValues[i], i)), b.push(mp(bobValues[i], i));
        
        int x,y;
        bool f[aliceValues.size()];
        memset(f, 1, sizeof(f));
        x = y = 0;
        
        for(int i=0; i<aliceValues.size(); i++)
        {
            while(!f[a.top().ss]) a.pop();
            while(!f[b.top().ss]) b.pop();
            
            if(i%2 == 0) {
                x+=a.top().ff;
                f[a.top().ss] = 0;
                a.pop();
            }
            
            else {
                y+=b.top().ff;
                f[b.top().ss] = 0;
                b.pop();
            }
             
        }
        
        if(x>y) return 1;
        if(y>x) return -1;
        return 0;
    }
};

int main()
{
    Solution s;
    s.stoneGameVI({1,2}, {3,1});
}