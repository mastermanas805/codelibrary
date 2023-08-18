// https://leetcode.com/problems/detonate-the-maximum-bombs

#include<bits/stdc++.h>
using namespace std;
class Solution {
    long long distance(vector<int> &A, vector<int> &B) {
        return (A[0] - B[0]) * 1L * (A[0] - B[0]) + (A[1] - B[1]) * 1L * (A[1] - B[1]);
    }
    void dfs(int curr, vector<int> adjList[], vector<bool> &visited, int &count) {
        if(visited[curr]) return;
        visited[curr] = true;
        count++;
        for(int next: adjList[curr]) {
            dfs(next, adjList, visited, count);
        }
    }
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<int> adjList[n];
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                long long distSquare = distance(bombs[i], bombs[j]);
                if(distSquare <= bombs[i][2] * 1L * bombs[i][2]) {
                    adjList[i].push_back(j);
                }
                if(distSquare <= bombs[j][2] * 1L * bombs[j][2]) {
                    adjList[j].push_back(i);
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            vector<bool> visited(n, false);
            int count = 0;
            dfs(i, adjList, visited, count);
            ans = max(ans, count);
        }
        return ans;
    }
};