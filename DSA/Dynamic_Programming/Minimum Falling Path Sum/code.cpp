// https://leetcode.com/problems/minimum-falling-path-sum/

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int m = matrix[0].size(), n = matrix.size();
        for(int i=1;i<n;i++)
            for(int j=0;j<m;j++)
                matrix[i][j]+=min({j-1>-1?matrix[i-1][j-1]:INT_MAX, matrix[i-1][j], j+1<m? matrix[i-1][j+1]: INT_MAX});
        
        return *min_element(matrix[n-1].begin(), matrix[n-1].end());
    }
};