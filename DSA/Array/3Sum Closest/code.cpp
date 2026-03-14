#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target)
    {
        sort(begin(num), end(num));

        unsigned int n = num.size();
        unsigned int distance{INT_MAX};
        int result;

        for (int i = 0; i < n - 2; i++)
        {
            if (i > 0 && num[i - 1] == num[i]) continue;

            int a = num[i];
            int low = i + 1;
            int high = n - 1;

            while (low < high)
            {
                int b = num[low];
                int c = num[high];
                int sum = a + b + c;
                if (sum - target == 0){ return target; }
                else
                {
                    if (abs(sum - target) < distance)
                    {
                        distance = abs(sum - target);
                        result = sum;
                    }

                    if (sum - target > 0)
                    {
                        while (high > 1 && num[high] == num[high - 1]) high--;
                        high--;
                    }
                    else
                    {
                        while (low < n-1 && num[low] == num[low + 1]) low++;
                        low++;
                    }
                }
            }
        }

        return result;
    }
};

int main()
{
    vector<int> in = {-1,2,1,-4};
    int target = 1;
    Solution s;
    cout<<"The sum that is closest to the target is "<<s.threeSumClosest(in, target)<<endl;
}