#include<bits/stdc++.h>
#define mod 1000000007;
using namespace std;

class Solution {
public:
    int dp[100][201];
    int res=0;
    int ans=0;
    int sol(vector<int>& loc, int start, int fin, int fuel){
        if(fuel<0)return 0;
        if(dp[start][fuel]!=-1)return dp[start][fuel];
        int ans=0;
        if(start==fin){ans++;}
        for(int i=0;i<loc.size();i++){
            if(i==start)continue;
            int fuel_left=fuel-abs(loc[start]-loc[i]);
            int temp=sol(loc,i,fin,fuel_left);
            ans=(ans+temp)%mod;
        }
            return dp[start][fuel]=ans;;
        
    }
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        memset(dp,-1,sizeof dp);
    return sol(locations,start,finish,fuel);
    }
};

int main()
{
    vector<int> v = {2,3,6,8,4};
    int start = 1, finish = 3, fuel = 5;
    Solution s;
    cout<<"No of paths is "<<s.countRoutes(v,start, finish, fuel)<<endl;
}