class Solution {
public:
    char ans;
    char nextGreatestLetter(vector<char>& letters, char target) {
        ans = letters[0];
        bsearch(letters,0,letters.size() - 1, target);
        return ans;
    }
    
    void bsearch(vector<char>& v, int l, int r, int x)
    {
        if(r>=l)
        {
            int mid = l + (r-l)/2;
            
            if(v[mid] == x) 
                l = mid+1;
            
            else if(v[mid] < x)
                l = mid+1;
            
            else 
            {
                 this->ans = v[mid];
                 r = mid - 1;
            }
            
            bsearch(v,l,r,x);
        }
    }
};