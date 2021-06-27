#include <bits/stdc++.h>
using namespace std;

void solve() {
	int H, L;
	cin >> L >> H;
	string S; cin >> S;
	int cnt = 0;
	for (char c : S) {
		if (c == '0')
			cnt++;
		else {
			if (cnt > H / 2) {
				H = 2 * (H - cnt);
			}
			cnt = 0;
			if(H < 0) break;
		}
	}
	if (cnt > H / 2)
		H = 2 * (H - cnt);
	if (H <= 0) cout << "YES\n";
	else cout << "NO\n";
}


int main() {

	int t = 1;
	cin >> t;
	while (t--)
		solve();
	return 0;
}

