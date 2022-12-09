#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;

struct entry {
	pii rc;
	int dp;
};

int main() {
	int n;
	cin >> n;
	string s;
	vi A(n);
	for (int& a : A) {
		cin >> s;
		a = s.size();
	}

	int lo = *max_element(A.begin(), A.end());
	int hi = accumulate(A.begin(), A.end(), 0) + n - 1;

	int bestK = -1;
	int ans = 0;

	vector<entry> S;
	S.reserve(n - 1);
	for (int k = lo; k <= hi; k++) {
		int r = -1, c = hi;
		S.clear();
		for (int a : A) {
			bool p = c;
			if (a + p + c > k) {
				r++;
				c = 0;
				p = false;
			}
			if (!p) {
				c = a;
				continue;
			}
			S.push_back({ {r, c}, 1 });
			c += a + 1;
		}
		int m = S.size();
		if (m == 0) continue;
		if (S.back().rc.first < ans) break;

		int cur = 1;
		int pos = 0;
		for (entry& e : S) {
			auto [r, c] = e.rc;
			while (pos < 0 || pos < m && S[pos].rc < pii(r - 1, c - 1)) pos++;
			while (pos < m && S[pos].rc <= pii(r - 1, c + 1)) {
				e.dp = max(e.dp, S[pos].dp + 1);
				cur = max(cur, e.dp);
				pos++;
			}
			pos -= 3;
		}
		if (cur > ans) {
			ans = cur;
			bestK = k;
		}
	}
	cout << bestK << ' ' << ans;

}