bool comp(Job a, Job b)
{
    if(a.profit == b.profit) return a.dead < b.dead;
    return a.profit>b.profit;
}
    
class Solution 
{
    public:
    
    //Function to find the maximum profit and the number of jobs done.
    vector<int> JobScheduling(Job a[], int n) 
    { 
        sort(a, a+n, comp);
        int cnt = 0, p = 0, mx=a[0].dead;
        for(int i=1;i<n;i++) mx = max(mx, a[i].dead);
        
        int slot[mx+1];
        memset(slot, -1, sizeof(slot));
        
        for(int i=0; i<n; i++)
          for(int j=a[i].dead; j>0; j--)
            if(slot[j] == -1)
             {
                 cnt++;
                 p+=a[i].profit;
                 slot[j] = i;
                 break;
             }
        
        return {cnt,p};
    } 
};