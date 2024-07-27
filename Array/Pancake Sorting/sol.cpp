class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> ret;
        for (int i = arr.size(); i > 0; i--) {
            int index = find(arr, i);

            if (index == i - 1)
                continue;
            if (index > 0) {
                ret.push_back(index + 1);
                flip(arr, index + 1);
            }

            ret.push_back(i);
            flip(arr, i);
        }

        return ret;
    }

    void flip(vector<int>& arr, int k) {
        for (int i = 0; i < k / 2; i++) {
            int x = arr[i];
            arr[i] = arr[k - 1 - i];
            arr[k - 1 - i] = x;
        }
    }

    int find(vector<int>& arr, int val) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == val)
                return i;
        }

        return 0;
    }
};