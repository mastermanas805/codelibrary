// https://takeuforward.org/interviews/strivers-sde-sheet-top-coding-interview-problems/
// https://leetcode.com/problems/sort-colors/
class Solution {
public:
    void sortColors(vector<int>& a) {
        int l=0,mid=0,r = a.size()-1;
        
        while(mid<=r)
        {
            switch(a[mid])
            {
                case 0:
                    swap(a[l++], a[mid++]);
                    break;
                case 1:
                    mid++;
                    break;
                case 2:
                    swap(a[mid], a[r--]);
                    break;
            }
        }
    }
};