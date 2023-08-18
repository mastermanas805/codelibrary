// https://leetcode.com/problems/random-pick-with-weight

// Time Complexity: O(n)
// Space Complexity: O(n)

#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<int> prefixSums;
public:
    Solution(vector<int> &w) {
        for (auto n : w)
            prefixSums.push_back(n + (prefixSums.empty() ? 
                0 : prefixSums.back()));
    }

    int pickIndex() {
        // generate a random number in the range of [0, 1]
        float randNum = (float) rand() / RAND_MAX;
        float target =  randNum * prefixSums.back();
        // run a linear search to find the target zone
        for (int i = 0; i < prefixSums.size(); ++i)
            if (target < prefixSums[i])
                return i;
        return prefixSums.size() - 1;
    }
};

int main() {
    vector<int> w;
    w.push_back(1);
    w.push_back(3);
    Solution* obj = new Solution(w);
    cout<<obj->pickIndex()<<endl;
    delete obj;

    return 0;
}
