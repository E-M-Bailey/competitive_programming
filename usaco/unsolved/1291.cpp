#include <bits/stdc++.h>

using namespace std;

struct ent {
	int64_t x, y, t;
}

int main() {
	int g, n;
	cin >> g >> n;
	vector<ent> G(g);
	for (int i = 0; i < g; i++) {
		cin >> G[i].x >> G[i].y > G[i].t;
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int64_t x, y, t;
		cin >> x >> y >> t;
		bool I = true;
		for (auto [xx, yy, tt] : G) {
			int64_t dx = x - xx, dy = y - yy, dt = t - tt;
			I &= abs(dt) > sqrt(dx * dx + dy * dy) - 1e-9;
		}
		ans += I;
	}
}