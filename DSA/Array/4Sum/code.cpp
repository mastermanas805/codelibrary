// https://leetcode.com/problems/4sum/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        if(n < 4) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        
        for(int i = 0; i<n; i++)
        {
            for(int j = i+1; j<n; j++)
            {
                int front = j+1, rear = n-1, t = target -(nums[i] + nums[j]), sum;
                
                while(front<rear)
                {
                    sum = nums[front] + nums[rear];

                    if(sum < t) front++;

                    else if(sum > t) rear--;

                    else
                    {
                        vector<int> quad = {nums[i], nums[j], nums[front], nums[rear]};
                        ret.push_back(quad);

                        while(front+1<n && nums[front] == quad[2]) front++;
                        while(rear-1>=0 && nums[rear] == quad[3]) rear--;
                    }
                }
                
                while(j+1<n && nums[j+1] == nums[j]) j++;
            } 
            while(i+1<n && nums[i+1] == nums[i]) i++;
        }
                                                            
        return ret;
    }
};