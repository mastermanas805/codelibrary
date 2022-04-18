// https://leetcode.com/problems/unique-binary-search-trees/

class Solution {
public:
    int numTrees(int n) {
        int a[n+1], count;
        a[0] = a[1]  = 1;
        
        for(int i =2; i<=n; i++)
        {
            count = 0;
            for(int j=0; j< i/2 ; j++) count+= a[j]*a[i-1-j];
            
            count*=2;
            if(i%2) count+= a[i/2]*a[i/2];
            
            a[i] = count;
        }
        
        return a[n];
    }
};