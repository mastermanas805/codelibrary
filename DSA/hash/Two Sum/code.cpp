#define pb push_back
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,vector<int>> mp;
        for(int i=0; i<nums.size(); i++)
        {
            mp[nums[i]].pb(i);
            if(mp.find(target-nums[i]) != mp.end())
            {
                if(2*nums[i] == target) 
                {
                    if(mp[target - nums[i]].size() == 1) continue;
                    
                    for(int j:mp[target - nums[i]]) if(j != i) return {i,j};
                }
                
                else return {i, mp[target - nums[i]][0]};
            }
        }
        return {};
    }
};