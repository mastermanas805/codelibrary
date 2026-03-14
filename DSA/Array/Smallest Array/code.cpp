#include<bits/stdc++.h>
using namespace std;

class nearest
{
    vector<int> a;
    int n;
    nearest(vector<int> arr)
        {
            a = arr;
        }

    bool comp(int i1, int i2)
    {
        return abs(i1 - n)< abs(i2 - n);
    }

    int cal(int num)
    {
        n = num;
        int f = 0, r = a.size(), m,s,i;
        s = INT_MAX;
        while(f<r)
        {
            m = (f+r)/2;
            if(s > abs(n - a[m]))
            {
                s = abs(n - a[m]);
                i = a[m];
            }
                
            if(abs(n - a[m]) >=0)
            f = m+1;
            else
            r = m;
        }

        return i;
    }

};

vector<int> smallestDiffrence(vector<int> arrayOne, vector<int> arrayTwo)
{
    sort(arrayOne.begin(), arrayOne.end());

    vector<int> res = {arrayOne[0], arrayTwo[0]};
    int x;

    for(auto i: arrayOne)
       {
          x = nearest(arrayTwo, i);
          if(abs(i-x) < abs(res[0]-res[1]))
                 res[0] = i, res[1] = x;
       }
    
    return res;
}

int main()
{
    vector<int> arrayOne = {-1, 5, 10, 20, 28, 3};
    vector<int> arrayTwo = {26, 34, 135, 15, 17};
    smallestDiffrence(arrayOne, arrayTwo);

}