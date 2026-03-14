int solve(vector<int> &a, int b) {

    int xorr = 0, cnt = 0, n = a.size();
    map<int,int> mp;

    for(int i=0; i<n; i++)
    {
        xorr^=a[i];
        if(xorr == b) cnt++;

        if(mp.find(xorr^b) != mp.end()) cnt+=mp[xorr^b];

        mp[xorr]++;
    }

    return cnt;
}
