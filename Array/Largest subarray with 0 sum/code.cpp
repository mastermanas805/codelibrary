// https://practice.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1#

class Solution{
    public:
    int maxLen(vector<int>&a, int n)
    {   
        int count = 0, sum = 0;
        map<int,int> mp;
        mp[0] = -1;
        
        for(int i=0; i<n; i++)
        {
            sum+=a[i];
            
            if(mp.find(sum) != mp.end())
                count= max(count, (i - mp[sum]));
            
            else
              mp[sum] = i;
        }
        
        return count;
    }
};