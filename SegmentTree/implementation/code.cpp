#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 1e5; // Adjust based on problem constraints
int seg[4 * MAXN];
int a[MAXN];

void build(int ind, int low, int high) {
    if (low == high) {
        seg[ind] = a[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid);
    build(2 * ind + 2, mid + 1, high);
    seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
}

int query(int ind, int low, int high, int l, int r) {
    if (low >= l && high <= r) {
        return seg[ind];
    }
    if (high < l || low > r) return INT_MIN;
    int mid = (low + high) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);
    return max(left, right);
}

int main() {
    int n = 5;
    int inputArray[] = {1, 3, 2, 7, 9};  // Example input array

    for (int i = 0; i < n; i++) {
        a[i] = inputArray[i];
    }

    build(0, 0, n - 1);

    int q = 3;  // Number of queries
    vector<pair<int, int>> queries = {{1, 3}, {0, 4}, {2, 4}};  // Example queries

    for (int i = 0; i < q; i++) {
        int l = queries[i].first;
        int r = queries[i].second;
        cout << "Maximum value in range [" << l << ", " << r << "] is: " 
             << query(0, 0, n - 1, l, r) << endl;
    }

    return 0;
}