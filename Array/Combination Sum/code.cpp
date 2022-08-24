// https://leetcode.com/problems/combination-sum/

class Solution {
public:
    // i represents the ith index 
    void IsCombinationSum(vector<int>& candidates,int target,int i,vector<vector<int>>&res,vector<int>&ds)
    {
        if(i==size(candidates)){
            // maybe i found out the target or not 
            if(target==0)
            {
                res.push_back(ds);
            }
            return ;
        }
      // pickup the element
        if(target>=candidates[i])
        {
            ds.push_back(candidates[i]);
            IsCombinationSum(candidates,target-candidates[i],i,res,ds);
            ds.pop_back();  
        }
        // not picking the elment
         IsCombinationSum(candidates,target,i+1,res,ds);
    }
    
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
//    7     [2,3,6,7]--> [[2,2,3],[7]]
        vector<vector<int>>res;
        vector<int>ds;
          IsCombinationSum(candidates,target,0,res,ds);
        
      return res;
        
    }
};