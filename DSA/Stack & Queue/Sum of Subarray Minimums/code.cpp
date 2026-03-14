# define mx 1000000007
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        arr.push_back(0);
        long sum = 0, n = arr.size();
        int nsr[n];
        stack<int> s;

        for (int i = n - 1; i >= 0; i--) {
            while (!s.empty() && arr[s.top()] > arr[i])
                s.pop();
            if (s.empty()) {
                nsr[i] = -1;
            } else {
                nsr[i] = s.top();
            }
            s.push(i);
        }

        for (int i = 0; i < n - 1; i++) {
            int j = i;

            while (j <= n - 2) {
                int nextSmaller = nsr[j];
                if (nextSmaller == -1) {
                    sum = (sum + (arr[j] * (n - nextSmaller - 1)))%mx;
                    j = n;
                } else {
                    sum = (sum + (arr[j] * (nextSmaller - j)))%mx;
                    j = nextSmaller;
                }
            }
        }

        return sum;
    }
};