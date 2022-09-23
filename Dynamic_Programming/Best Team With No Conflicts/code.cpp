// https://leetcode.com/problems/best-team-with-no-conflicts/


int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = ages.size() + 1, sum, mx;
        vector<pair<int,int>> v;
        v.push_back({0,0});
        for(int i=0;i<n-1;i++) v.push_back({ages[i], scores[i]});
        
        sort(v.begin(), v.end());
        int dp[n];
        dp[0] = 0;
        for(int i=1;i<n;i++){
            sum = 0;
            mx = 0;
            for(int j=1;j<i;j++)
                if(v[j].first == v[i].first)
                    mx = max(mx, dp[j]);
                else if(v[j].second <= v[i].second)
                    mx = max(mx, dp[j]);
            
            dp[i] = v[i].second + mx;
        }
        
        return *max_element(dp, dp+n);
        
    }