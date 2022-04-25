// https://leetcode.com/problems/3sum/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        
        for(int i = 0; i<n; i++)
        {
            int front = i+1, rear = n-1, target = -nums[i], sum;
            
            while(front<rear)
            {
                sum = nums[front] + nums[rear];
                
                if(sum < target) front++;
                
                else if(sum > target) rear--;
                
                else
                {
                    vector<int> triplet = {nums[i], nums[front], nums[rear]};
                    ret.push_back(triplet);
                    
                    while(front+1<n && nums[front] == triplet[1]) front++;
                    while(rear-1>=0 && nums[rear] == triplet[2]) rear--;
                }
            }
            
            while(i+1<n && nums[i+1] == nums[i]) i++;
        }
                                                            
        return ret;
    }
};