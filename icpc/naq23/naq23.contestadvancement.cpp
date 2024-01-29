#include <bits/stdc++.h>

using namespace std;

int main() {
	int n,k,c;
	cin >> n >> k >> c;
	vector<pair<int,int>> extra;
	vector<pair<int,int>> ret;
	unordered_map<int,int> cnt;
	for (int i = 0; i<n; i++) {
		int id, s;
		cin >> id >> s;
		if (int(ret.size()) >= k || cnt[s] == c) {
			extra.emplace_back(i, id);
		} else {
			cnt[s]++;
			ret.emplace_back(i, id);
		}
	}
	for (int i = 0; i<int(extra.size()) && int(ret.size()) < k; i++) {
		ret.push_back(extra[i]);
	}
	sort(ret.begin(), ret.end());
	for (auto elem : ret) {
		cout << elem.second << '\n';
	}
}