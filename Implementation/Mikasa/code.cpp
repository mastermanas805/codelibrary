#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define pii pair<int,int>
int bitcount(int x){ int count = 0; while(x) { count++; x >>= 1; } return count; }

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    ++m;
    int ans = 0;
    for (int k = 30; k >= 0 and n < m; k--) {
      if ((n >> k & 1) == (m >> k & 1)) continue;
      if (m >> k & 1) ans |= 1 << k, n |= 1 << k;
    }
    cout << ans << '\n';
  }
  return 0;
}