// https://leetcode.com/problems/single-threaded-cpu/


// Time Complexity: O(nlogn)
// Space Complexity: O(n)

// Approach:
// 1. Sort the tasks based on enqueue time.
// 2. Create a min heap to store the tasks based on processing time.
// 3. Iterate over the tasks and push all the tasks whose enqueue time <= currTime into the heap.
// 4. Pop the top task from the heap and complete it. Increment currTime by processing time of the task.
// 5. Repeat step 3 and 4 until all the tasks are completed.


#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        // Sort based on min task processing time or min task index.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> nextTask;

        // Store task enqueue time, processing time, index.
        vector<array<int, 3>> sortedTasks;
        for (int i = 0; i < tasks.size(); ++i) {
            sortedTasks.push_back({tasks[i][0], tasks[i][1], i});
        }

        sort(sortedTasks.begin(), sortedTasks.end());
        vector<int> tasksProcessingOrder;

        long long currTime = 0;
        int taskIndex = 0;

        // Stop when no tasks are left in array and heap.
        while (taskIndex < tasks.size() || !nextTask.empty()) {
            if (nextTask.empty() && currTime < sortedTasks[taskIndex][0]) {
                // When the heap is empty, try updating currTime to next
                // task's enqueue time.
                currTime = sortedTasks[taskIndex][0];
            }

            // Push all the tasks whose enqueueTime <= currtTime into the heap.
            while (taskIndex < sortedTasks.size() && currTime >= sortedTasks[taskIndex][0]) {
                nextTask.push({sortedTasks[taskIndex][1], sortedTasks[taskIndex][2]});
                ++taskIndex;
            }

            auto [processTime, index] = nextTask.top();
            nextTask.pop();

            // Complete this task and increment currTime.
            currTime += processTime;
            tasksProcessingOrder.push_back(index);
        }

        return tasksProcessingOrder;
    }
};