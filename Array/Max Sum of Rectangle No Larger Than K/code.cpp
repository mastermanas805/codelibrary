#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int l = 0;
        int r = 0;
        int res = INT_MIN;
        for(l = 0; l < matrix[0].size(); l++){
            vector<int> sum(matrix.size(),0);
            
            for(r = l; r < matrix[0].size(); r++){
                for(int i = 0; i < matrix.size(); i++){
                    sum[i] += matrix[i][r];
                }
                
                for(int i = 0; i < sum.size(); i++){
                    int s = sum[i];
                    for(int j = i+1; j < sum.size(); j++){
                        if(s <= k) res = max(res, s);
                        s += sum[j];
                    }
                    if(s <= k)
                        res = max(res, s);
                }
                
                if(res == k)
                    return k;
            }
        }
        return res;
    }
};

int main()
{
    vector<vector<int>> v = {
                             {1,0,1},
                             {0,-2,3}
                            };
    int k =2;
    Solution s;
    cout<<s.maxSumSubmatrix(v,k);
}
