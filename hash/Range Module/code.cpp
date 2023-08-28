// https://leetcode.com/problems/range-module/description/

#include<bits/stdc++.h>
using namespace std;

class RangeModule {
    // endToStart: end -> start
    map<int, int> endToStart;
public:
    /*
    Adds the half-open interval [left, right), 
    tracking every real number in that interval. Adding an interval 
    that partially overlaps with currently tracked numbers should add any 
    numbers in the interval [left, right) that are not already tracked.
    */
    void addRange(int left, int right) {
        // find the first interval that has start >= left
        // and merge all intervals that have start <= right
        // and end >= left
        // and add the new interval [left, right)
        // and remove all intervals that have start <= left
        // and end >= right
        map<int, int>::iterator it = endToStart.lower_bound(left);
        map<int, int>::iterator next = it;
        
        while (next != endToStart.end() && next->second <= right) {
            left = min(left, next->second);
            right = max(right, next->first);
            next++;
        }
        
        endToStart.erase(it, next);
        endToStart[right] = left;
    }
    
    /*
    Returns true if every real number in the interval 
    [left, right) is currently being tracked, and false otherwise.
    */
    bool queryRange(int left, int right) {
        // find the first interval that has start >= left
        // and check if it has start <= left and end >= right
        
        map<int, int>::iterator it = endToStart.lower_bound(left);
        if (it == endToStart.end()) {
            return false;
        }
        
        return it->second <= left && it->first >= right;
    }
    
    /*
    Stops tracking every real number 
    currently being tracked in the half-open interval [left, right).
    */
    void removeRange(int left, int right) {
        // find the first interval that has start >= left
        // and merge all intervals that have start <= right
        // and end >= left
        // and remove the interval [left, right)
        // and add the intervals [start, left) and [right, end)

        map<int, int>::iterator it = endToStart.lower_bound(left);
        if (it == endToStart.end()) {
            return;
        }
        
        vector<pair<int, int>> toBeAdded;
        map<int, int>::iterator next = it;
        while (next != endToStart.end() && next->second < right) {
            if (next->second < left) {
                toBeAdded.push_back(make_pair(next->second, left));
            }
            
            if (next->first > right) {
                toBeAdded.push_back(make_pair(right, next->first));
            }
            
            next++;
        }
        
        endToStart.erase(it, next);
        for (auto& x : toBeAdded) {
            endToStart[x.second] = x.first;
        }
    }
};

int main()
{
    freopen("input.txt", "r", stdin);

    RangeModule* obj = new RangeModule();
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string opr;
        cin>>opr;

        if( opr == "addRange"){
            int left, right;
            cin >> left >> right;
            obj->addRange(left, right);
        }else if( opr == "removeRange"){
            int left, right;
            cin >> left >> right;
            obj->removeRange(left, right);
        }else if( opr == "queryRange"){
            int left, right;
            cin >> left >> right;
            bool param_3 = obj->queryRange(left, right);
            cout << param_3 << endl;
        }
    
    

    }

}