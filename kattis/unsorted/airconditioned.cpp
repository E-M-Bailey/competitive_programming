#include <bits/stdc++.h>

using namespace std;
int main(int argc, const char* argv[]) {
	if (argc > 1) {
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int n; cin >> n;
	vector<pair<int,int>> a(n);
	for (int i = 0; i<n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	sort(a.begin(), a.end(), [](auto x, auto y) {
		if (x.first != y.first) return x.first < y.first;
		return x.second > y.second;
	});
	int s = a[0].first, e = a[0].second, ret = 1;
	for (int i = 1; i<n; i++) {
		if (a[i].first > e) {
			ret++;
			s = a[i].first;
			e = a[i].second;
 		} else {
			s = max(s, a[i].first);
			e = min(e, a[i].second);
		}
	}
	cout << ret << '\n';
	return 0;
}