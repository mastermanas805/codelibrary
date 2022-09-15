// https://leetcode.com/problems/3sum-with-multiplicity/

class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        
        map<int,long long> m;
        long long ans=0;
        
        for(auto i:arr)
            m[i]++;
                
        for(auto it1:m)
        {
            for(auto it2:m)
            {
                int i=it1.first,j=it2.first,k=target-i-j;
                
    //Case 1  all the three are equal--> (n*n-1*n-2)/3! as all the three are same
                if(i==j and j==k) 
                    ans+= (m[i]*(m[i]-1)*(m[i]-2))/6;
                
     //Case 2  all the three are equal--> (n*n-1)/2! as two of them are same       
                else if(i==j and j!=k)
                     ans+=(m[i]*(m[i]-1)*m[k])/2;
       
        //Case 3 all distinct
                else if(i<j and j<k)
                    ans+=m[i]*m[j]*m[k];
            }
        }
        
        return ans%1000000007;
    }
};