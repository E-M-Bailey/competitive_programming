// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;

int main()
{
	int n;
	cin >> n;
	vector<int> F(n), A(2 * n);
	vector<pair<int, int>> E(n);
	vector<bool> V(n);
	for (int i = 0; i < n; ++i)
	{
		auto &[u, v] = E[i];
		cin >> u >> v;
		A[u] = A[v] = i;
		int s = u + v;
		F[(s >= 2 * n ? s - 2 * n : s) / 2] += s & 1;
	}
	int s = (rng::max_element(F) - begin(F)) * 2 + 1;

	vector<tuple<int, int, int>> M;
	vector<int> cur;
	for (int i = 0; i < n; ++i)
	{
		auto [ui, vi] = E[i];
		if (V[i])
			continue;
		cur.assign({ i });
		do
		{
			int u = s - E[cur.back()].second;
			u = u < 0 ? u + 2 * n : u;
			int j = A[u];
			V[j] = true;
			cur.push_back(j);
			if (E[j].first != u)
				swap(E[j].first, E[j].second);
		}
		while (cur.back() != i);
		if (size(cur) == 2)
			continue;
		for (int j = 0; j < size(cur) - 1; ++j)
			M.emplace_back(cur[j], E[cur[j]].first, E[cur[j + 1]].first);
	}
	cout << size(M);
	for (auto [p, s, e] : M)
		cout << '\n' << p << ' ' << s << ' ' << e;
}
