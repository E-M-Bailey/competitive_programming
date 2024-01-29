#include <bits/stdc++.h>

using namespace std;

static constexpr const int mod = 9302023;

int main() {
	vector<string> candidates{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	string s; cin >> s;
	auto n = s.size();
	vector<int> dist_dp(n + 1, 1e9 + 10);
	dist_dp[0] = 0;
	for (size_t i = 1; i<=n; i++) {
		dist_dp[i] = min(dist_dp[i], dist_dp[i-1] + 1);
		for (const auto& elem : candidates) {
			if (i >= elem.size() && s.substr(i - elem.size(), elem.size()) == elem) {
				dist_dp[i] = min(dist_dp[i], (i >= elem.size() ? dist_dp[i-elem.size()] : 0) + 1);
			}
		}
	}
	vector<int> cnt_dp(n + 1);
	cnt_dp[0] = 1;
	for (size_t i = 1; i<=n; i++) {
		if (dist_dp[i] == dist_dp[i-1] + 1) {
			cnt_dp[i] = (cnt_dp[i] + cnt_dp[i-1]) % mod;
		}
		for (const auto& elem : candidates) {
			if (i >= elem.size() && (i >= elem.size() ? dist_dp[i - elem.size()] : 0) + 1 == dist_dp[i] && s.substr(i - elem.size(), elem.size()) == elem) {
				cnt_dp[i] = (cnt_dp[i] + (i >= elem.size() ? cnt_dp[i-elem.size()] : 0)) % mod;
			}
		}
	}
	cout << dist_dp.back() << '\n';
	cout << cnt_dp.back() << '\n';
}