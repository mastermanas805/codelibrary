// https://leetcode.com/problems/meeting-rooms-ii/

// Time Complexity: O(NlogN)
// Space Complexity: O(N)

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int rooms = 0;
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> pq;
        for(auto inter: intervals) {
            int st = inter[0], en = inter[1];
            while(!pq.empty() && pq.top() <=st) pq.pop();
            pq.push(en);
            rooms = max(rooms, (int)pq.size());
        }
        return rooms;
    }
};