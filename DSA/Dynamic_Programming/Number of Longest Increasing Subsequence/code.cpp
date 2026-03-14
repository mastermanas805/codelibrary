class Solution {
public:
    int findNumberOfLIS(vector<int>& words) {
        int n = words.size();
        vector<int> dp(n, 1);
        vector<int> occurences(n, 0);

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (words[i] < words[j])
                    dp[i] = max(dp[i], 1 + dp[j]);
            }

            for (int j = i + 1; j < n; j++) {
                if (words[i] < words[j] && dp[i] == dp[j] + 1)
                    occurences[i] += occurences[j];
            }
            occurences[i] = dp[i] == 1 ? 1 : occurences[i];
        }

        int mx = *max_element(dp.begin(), dp.end());
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] == mx)
                cnt += occurences[i];
        }

        return cnt;
    }
};