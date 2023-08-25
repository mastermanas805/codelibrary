// https://leetcode.com/problems/palindrome-partitioning-ii/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dp;
    bool isPallindrom(string &s, int i, int j){
        int n = j-i+1;

        for(int a=0;a < n/2; a++)
            if(s[i+a] != s[j-a])
                return false;
        
        return true;
    }

    int cut(string &s, int i, int n){
        if(i == n) return 0;
        if(dp[i] != -1) return dp[i];

        int mn = 3001;    

        for(int j=i; j<n; j++){
            if(isPallindrom(s,i,j)){
                mn = min(mn, 1 + cut(s, j+1, n));
            }
        }

        return dp[i] = mn;
    }


    int minCut(string s) {
        dp = vector<int>(s.length(), -1);
        return cut(s, 0, s.length()) - 1;
    }
};

int main(){
    Solution s;
    string input;
    // read input from file input.txt
    ifstream infile;
    infile.open("input.txt");
    infile>>input;
    infile.close();
  
    // I want to calculate time taken 
    clock_t start, end;
    start = clock();
    // call function and store result in ans
    int ans = s.minCut(input);
    // stop clock and calculate time taken
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout<<ans<<endl;
    cout<<"Time taken by program is : "<<fixed<<time_taken<<setprecision(5)<<endl;
     // I want to calculate memory used in megabytes
    int memory_used = 0;
    memory_used = sizeof(s.dp); // size of dp array in unit bytes
    cout<<float(memory_used)/(1024*1024)<<endl;


 
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)