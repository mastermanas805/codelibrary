#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& arr, int k) 
    {
      // create auxiliary hash array to count frequency
    // of remainders
    int mod[k], n= arr.size();
    memset(mod, 0, sizeof(mod));
 
    // Traverse original array and compute cumulative
    // sum take remainder of this current cumulative
    // sum and increase count by 1 for this remainder
    // in mod[] array
    int cumSum = 0;
    for (int i = 0; i < n; i++) {
        cumSum += arr[i];
 
        // as the sum can be negative, taking modulo twice
        mod[((cumSum % k) + k) % k]++;
    }
 
    int result = 0; // Initialize result
 
    // Traverse mod[]
    for (int i = 0; i < k; i++)
 
        // If there are more than one prefix subarrays
        // with a particular mod value.
        if (mod[i] > 1)
            result += (mod[i] * (mod[i] - 1)) / 2;
 
    // add the elements which are divisible by k itself
    // i.e., the elements whose sum = 0
    result += mod[0];
 
    return result;
    }
};

int main()
{
    vector<int> arr = {4,5,0,-2,-3,1};
    int n = 5;
    Solution s;
    cout<<s.subarraysDivByK(arr, n);
}