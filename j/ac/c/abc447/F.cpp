#include <bits/extc++.h>

using namespace std;

namespace
{
template<typename C, integral T = int>
[[nodiscard]] constexpr int sz(const C& c) noexcept
{
	return static_cast<T>(size(c));
}

pair<int, int> dfs(int u, int v, vector<vector<int>> &G)
{
	int d = sz(G[v]);
	int c = d - (u != v);
	int am = 0, am2 = 0, bm = 0;
	for (int w : G[v])
	{
		if (w == u)
			continue;
		auto [a, b] = dfs(v, w, G);
		if (a > am)
			swap(a, am);
		if (a > am2)
			swap(a, am2);
		if (b > bm)
			swap(b, bm);
	}
	return { c < 2 ? 0 : c == 2 ? 1 : 1 + am, max(bm, d < 2 ? 0 : d == 2 ? 1 : d == 3 ? 1 + am : 1 + am + am2) };
}
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		vector<vector<int>> G(n);
		for (int i = 1; i < n; ++i)
		{
			int u, v;
			cin >> u >> v;
			G[--u].push_back(--v);
			G[v].push_back(u);
		}
		cout << dfs(0, 0, G).second << '\n';
	}
}
