#define pb push_back
class Solution {
public:
    void compute(int n, int k, vector<int>& v, int num, int i)
    {
        if(i == n) 
        {    
            v.pb(num);
            return;
        }
        
        if(num%10 + k < 10)
            compute(n,k,v,num*10 + num%10 + k,i+1);
        if(num%10 - k >= 0)
            compute(n,k,v,num*10 + num%10 - k,i+1);
    }
    
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> v;
        if (k ==0)
         {   int x;
            for(int i=1; i<10; i++)
                {
                    x = 0;
                    for(int j=0; j<n; j++)
                        x = x*10 + i;
                    v.pb(x);
                }
             }       
        
        else
            for(int i=1; i<10; i++)
                compute(n,k,v,i,1);
        return v;
    }
};