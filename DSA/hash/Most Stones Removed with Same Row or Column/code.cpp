#include <bits/stdc++.h>
using namespace std;

int removeStones(vector<vector<int>> stones) {
    vector<pair<set<int>, set<int>>> dsList;
    for(auto stone: stones) {
        bool found = false;
        for(auto ds: dsList) {
            if( ds.first.find(stone[0]) != ds.first.end() 
                || ds.second.find(stone[1]) != ds.second.end() ) {
                    ds.first.insert(stone[0]);
                    ds.second.insert(stone[1]);
                    found = true;
                    break;
                }
        }
        if(!found)
            dsList.push_back({{stone[0]}, {stone[1]}});
    }

    return stones.size() - dsList.size();
}

int main()
{
    std::cout<<removeStones({{0,0},{0,2},{1,1},{2,0},{2,2}});

    return 0;
}