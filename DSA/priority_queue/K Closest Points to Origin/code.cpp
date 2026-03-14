// https://leetcode.com/problems/k-closest-points-to-origin/

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<double, vector<int>>, vector<pair<double, vector<int>>>, greater<pair<double, vector<int>>>> pt;

        for (vector<int> i : points)
            pt.push({sqrt(i[0] * i[0] + i[1] * i[1]), i});

        vector<vector<int>> ret;
        for (int i = 0; i < k; i++) {
            pair<double, vector<int>> p = pt.top();
            pt.pop();
            ret.push_back(p.second);
        }

        return ret;
    }
};
