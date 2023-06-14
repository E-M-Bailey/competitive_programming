#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define len(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	// #ifdef DBG
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	// #endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n,q; cin >> n;
	vector<int> a(n);
	for (int i = 0;i<n; i++) cin >> a[i];
	unordered_map<int, vector<int>> buckets, by_pos;
	for (int i = 0;i<n; i++) {
		by_pos[a[i]].push_back(i);
	}
	cin >> q;
	vector<vector<int>> B(q);
	vector<int> ret(q), start(q);
	for (int i = 0; i<q; i++) {
		int m; cin >> start[i] >> m;
		start[i]--;
		ret[i] = start[i];
		B[i].resize(m);
		vector<int> lb;
		for (int j = 0;j<m; j++) {
			cin >> B[i][j];
			buckets[B[i][j]].push_back(i);
			lb.push_back(lower_bound(begin(by_pos[B[i][j]]), end(by_pos[B[i][j]]), start[i]) - begin(by_pos[B[i][j]]));
		}
		int low = start[i]+1, high = n;
		while (low <= high) {
			auto mid = low + (high - low) / 2;
			int total = 0;
			for (int j = 0;j<m; j++) {
				auto p = lower_bound(all(by_pos[B[i][j]]), mid) - begin(by_pos[B[i][j]]);
				total += p - lb[j];
			}
			if (total == mid-start[i]) {
				ret[i] = mid;
				low = mid+1;
			} else {
				high = mid-1;
			}
		}
	}
	for (int i = 0;i<q; i++) {
		cout << (ret[i]-start[i]) << '\n';
	}
	
}

// g++ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out