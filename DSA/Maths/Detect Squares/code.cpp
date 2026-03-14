// https://leetcode.com/problems/detect-squares

#include<bits/stdc++.h>
using namespace std;

class DetectSquares {
public:
    int graph[1001][1001];
    DetectSquares() {
        memset(graph, 0, sizeof(graph));
    }

    int check(vector<pair<int,int>> p){
        int ret = 1;
        for(auto i:p){
            if(i.first < 0 || i.first > 1000 || i.second < 0  || i.second > 1000)
                return 0;
            
            ret*=graph[i.first][i.second];
        }
        return ret;
    }
    
    void add(vector<int> point) {
        graph[point[0]][point[1]]++;
    }
    
    int count(vector<int> point) {
        int j = point[1], cnt = 0;;
        for(int i=0; i<=1000; i++){
            if(i == point[0])
                continue;

            if(graph[i][j]){
                int distance = point[0] - i;
                cnt+=check({ {i,j}, {i, j - distance}, {point[0], point[1] - distance}});
                cnt+=check({ {i,j}, {i, j + distance}, {point[0], point[1] + distance}});
            }
        }
            return cnt;
    }
};

