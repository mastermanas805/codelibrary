// https://leetcode.com/problems/subsets

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        

        for(int i=0;i<nums.size();i++){
            vector<vector<int>> v;

            for(int j=0;j<ret.size();j++){
                vector<int> x = ret[j];
                x.push_back(nums[i]);
                v.push_back(x);
            }
            v.push_back(vector<int>{nums[i]});

            ret.insert(ret.end(), v.begin(), v.end());

        }
        ret.push_back({});

        return ret;
    }
};