// https://leetcode.com/problems/edit-distance

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        
        vector<int> cur(m+1,0), prev(m+1,0);
        for(int i=0;i<m+1;i++) prev[i] = i;

        for(int i=1;i<n+1;i++){
            cur[0] = i;
            for(int j=1;j<m+1;j++){
                if(word1[i-1] == word2[j-1])
                    cur[j] = prev[j-1];
                else
                    cur[j] = 1 + min({
                                            cur[j-1], //insertion
                                            prev[j], //deletion
                                            prev[j-1] //replace
                                        });
            }
            prev = cur;
        }
        
        return prev[m];
    }
};