// https://practice.geeksforgeeks.org/problems/minimum-platforms-1587115620/1

class Solution{
    public:
    //Function to find the minimum number of platforms required at the
    //railway station such that no train waits.
    int findPlatform(int arr[], int dep[], int n)
    {
        sort(arr, arr + n);
        sort(dep, dep + n);
        
        int count = 1;
        
        int prev = 0;
        for (int i = 1; i < n; i++) {
               if (arr[i] - dep[prev] <= 0) {
                   count++;
               }  
               else {
                   prev++;
               }
        }
        
        return count;
   }
};