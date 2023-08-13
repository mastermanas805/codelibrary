// https://leetcode.com/problems/meeting-rooms-iii/
#include <bits/stdc++.h>

using namespace std;

// Define the Solution class
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Sort meetings by start time
        sort(meetings.begin(), meetings.end());
        
        // Create an array to keep track of room utilization
        int utilization[n];

        // Define priority queues for used and free rooms
        // 'used' queue stores the end time of meetings and the corresponding room
        // 'free' queue stores the indices of available rooms
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > used;
        priority_queue<int, vector<int>, greater<int> > free;

        // Initialize the free rooms and utilization array
        for(int i=0; i<n; i++){
            free.push(i);
            utilization[i] = 0;
        }

        // Process each meeting
        for(int i = 0; i < meetings.size(); i++){
            // Find all free rooms and update the 'free' queue
            while(!used.empty()  && used.top().first <= meetings[i][0]){
                free.push(used.top().second);
                used.pop();
            }
            
            if(!free.empty()){
                // Allocate an available room
                int room = free.top();
                free.pop();
                utilization[room]++;
                used.push({meetings[i][1], room});
            } else {
                // No free rooms available, allocate a room with least end time
                int duration = meetings[i][1] -  meetings[i][0];
                pair<int,int> p = used.top();
                used.pop();
                utilization[p.second]++;
                used.push({p.first + duration, p.second});
            }
        }

        // Find the index of the room with maximum utilization
        int maxUtilizationIndex = 0;
        for(int j=1; j<n; j++){
            if(utilization[j] > utilization[maxUtilizationIndex]){
                maxUtilizationIndex = j;
            }
        }

        // Return the index of the most booked room
        return maxUtilizationIndex;
    }
};

// Main function
int main() {
    Solution solution;

    // Test Case 1
    int n1 = 2;
    vector<vector<int>> meetings1 = {{0,10},{1,5},{2,7},{3,4}};
    cout << "Most booked room for Test Case 1: " << solution.mostBooked(n1, meetings1) << endl;

    // Test Case 2
    int n2 = 3;
    vector<vector<int>> meetings2 = {{1,20},{2,10},{3,5},{4,9},{6,8}};
    cout << "Most booked room for Test Case 2: " << solution.mostBooked(n2, meetings2) << endl;

    // Test Case 3
    int n3 = 100;
    vector<vector<int>> meetings3 = {{0,1}};
    cout << "Most booked room for Test Case 3: " << solution.mostBooked(n3, meetings3) << endl;

    return 0;
}
