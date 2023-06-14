#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int n, m, k;
	cin >> n >> m >> k;

	vi O(m);
	for (int &o : O)
	{
		cin >> o;
		o--;
	}
	vi C(k);
	for (int &c : C)
	{
		cin >> c;
		c--;
	}
	vi st{ 0 };

	vector<vi> G1(n), G2(n);
	rep(i, 0, n)
	{
		int a;
		cin >> a;
		G1[i].resize(a);
		for (int &w : G1[i])
		{
			cin >> w;
			w--;
			G2[w].push_back(i);
		}
	}

	const auto dist = [&](vi &S, vector<vi> &G)
	{
		vi D(n, INT_MAX);
		queue<pair<int, int>> Q;
		for (int s : S)
			Q.emplace(0, s);
		while (!Q.empty())
		{
			auto [d, v] = Q.front();
			Q.pop();
			if (D[v] < INT_MAX)
				continue;
			D[v] = d;
			for (int w : G[v])
				if (D[w] == INT_MAX)
					Q.emplace(d + 1, w);
		}
		return D;
	};

	auto D1 = dist(st, G1);
	auto D2 = dist(O, G2);
	auto D3 = dist(C, G2);
	int ans = INT_MAX;
	rep(i, 0, n)
	{
		int d1 = D1[i], d2 = D2[i], d3 = D3[i];
		//cerr << i << ' ' << d1 << ' ' << d2 << ' ' << d3 << endl;
		if (max({ d1, d2, d3 }) == INT_MAX)
			continue;
		ans = min(ans, d1 + d2 + d3);
	}
	if (ans == INT_MAX)
		cout << "impossible";
	else
		cout << ans;
}

// g+ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out