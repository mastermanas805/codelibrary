#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        vector<int> numbers;
        for (int i = 1; i < n; i++) {
            fact *= i; // This will result in (n-1)!
            numbers.push_back(i);
        }
        numbers.push_back(n);
        
        string res = "";
        k--; // Convert to 0-indexed for easier math
        
        while (true) {
            // Find which block k falls into
            int index = k / fact;
            res += to_string(numbers[index]);
            numbers.erase(numbers.begin() + index);
            
            if (numbers.size() == 0) break;
            
            // Update k for the next position
            k %= fact;
            // Update factorial for the next size: (n-2)!, (n-3)!...
            fact /= numbers.size();
        }
        
        return res;
    }
};

int main() {
    Solution s;
    cout<<s.getPermutation(3,6);
}