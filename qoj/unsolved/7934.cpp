#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<double, double>> p1(n);
	for (int i = 0; i<n; i++) {
		cin >> p1[i].first >> p1[i].second;
	}
	int m;
	cin >> m;
	vector<pair<double, double>> p2(m);
	for (int i = 0; i<m; i++) {
		cin >> p2[i].first >> p2[i].second;
	}
	auto ff = [&](double dx, double dy) {
		vector<pair<double, double>> pp1;
		for (const auto& p : p1) {
			pp1.emplace_back(p.first + dx, p.second + dy);
		}
		double ret = 0;
		for (int i = 0; i<m; i++) {
			for (int j = 0; j<n; j++) {
				auto ddx = p2[i].first - pp1[j].first;
				auto ddy = p2[i].second - pp1[j].second;
				ret = max(ret, sqrt(ddx * ddx + ddy * ddy));
			}
		}
		return ret;
	};
	auto f = [&](double x) {
		double low = -1e6, high = 1e6;
		for (int iter = 0; iter < 70; iter++) {
			auto m1 = low + (high - low) *  0.45;
			auto m2 = high - (high - low) * 0.45;
			auto f1 = ff(x, m1), f2 = ff(x, m2);
			if (f1 < f2) {
				high = m2;
			} else {
				low = m1;
			}
		}
		auto ret = (low + high) / 2;
		return make_pair(ret, ff(x, ret));
	};
	double low = -1e6, high = 1e6;
	for (int iter = 0; iter < 70; iter++) {
		auto m1 = low + (high - low) * 0.45;
		auto m2 = high - (high - low) * 0.45;
		auto [_, f1] = f(m1);
		auto [__, f2] = f(m2);
		if (f1 < f2) {
			high = m2;
		} else {
			low = m1;
		}
	}
	auto x = (low + high) / 2;
	auto [y, ret] = f(x);
	cout << setprecision(8) << fixed << ret << " " << x << " " << y << '\n'; 
}