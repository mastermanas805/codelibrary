#include<bits/stdc++.h>
#define mod 1000000007;
using namespace std;


class Solution {
public:
    int dp[100][201];
    
    
    Solution()
    {
        memset(dp,-1,sizeof dp);
    }
    
    
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        
        if(fuel<0)
            return 0;
        
        if(dp[start][fuel] !=-1)
            return dp[start][fuel];
        int ans = 0;
        
        if(start == finish)
            ans++;
        
        for(int i=0;i<locations.size();i++)
        {
            if(i == start)
                continue;
            
            int fuel_left = fuel - abs(locations[start] - locations[i]);
            int temp = countRoutes(locations, i, finish, fuel_left);
            ans = (ans + temp)%m;
        }
        
        return dp[start][fuel] = ans;
    }
};

int main()
{
    vector<int> v = {2,3,6,8,4};
    int start = 1, finish = 3, fuel = 5;
    Solution s;
    cout<<"No of paths is "<<s.countRoutes(v,start, finish, fuel)<<endl;
}