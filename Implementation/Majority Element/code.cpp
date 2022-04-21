// https://leetcode.com/problems/majority-element/
// Moore’s Voting Algorithm

class Solution {

public:
    int majorityElement(vector<int>& nums) {
        int count = 0, ele;
        for(int i: nums)
        {
            if(count == 0)
                ele = i;
            if(i == ele) count++;
            else count--;
        }
        return ele;
    }
};