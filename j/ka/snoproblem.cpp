#include <bits/stdc++.h>

using namespace std;

struct entry
{
	int b, c, d, e;
};

int n;

vector<vector<pair<int, int>>> G;

entry dfs(int v)
{
	vector<entry> A;
	for (auto [w, wt] : G[v])
	{
		G[w].erase(find(begin(G[w]), end(G[w]), pair{v, wt}));
		A.push_back(dfs(w));
		A.back().d += wt;
		A.back().e += wt;
	}

	int m = (int)A.size();

	vector<pair<int, int>> B(m), C(m), D(m), E(m);
	for (int i = 0; i < m; i++)
	{
		B[i] = {A[i].b, i};
		C[i] = {A[i].c, i};
		D[i] = {A[i].d, i};
		E[i] = {A[i].e, i};
	}
	sort(begin(B), end(B), greater<pair<int, int>>{});
	sort(begin(C), end(C), greater<pair<int, int>>{});
	sort(begin(D), end(D), greater<pair<int, int>>{});
	sort(begin(E), end(E), greater<pair<int, int>>{});

	entry ans{0, 0, 0, 0};

	if (m >= 1)
		ans.d = max(ans.d, D[0].first);

	ans.b = ans.d;
	if (m >= 1)
		ans.b = max(ans.b, B[0].first);
	if (m >= 2)
		ans.b = max(ans.b, D[0].first + D[1].first);

	ans.e = ans.b;
	if (m >= 1)
		ans.e = max(ans.e, E[0].first);
	if (m >= 2)
	{
		if (D[0].second == B[0].second)
			ans.e = max({ans.e, D[0].first + B[1].first, D[1].first + B[0].first});
		else
			ans.e = max(ans.e, D[0].first + B[0].first);
	}
	if (m >= 3)
		ans.e = max(ans.e, D[0].first + D[1].first + D[2].first);

	ans.c = ans.e;
	if (m >= 1)
		ans.c = max(ans.c, C[0].first);
	if (m >= 2)
	{
		ans.c = max(ans.c, B[0].first + B[1].first);
		if (D[0].second == E[0].second)
			ans.c = max({ans.c, D[0].first + E[1].first, D[1].first + E[0].first});
		else
			ans.c = max(ans.c, D[0].first + E[0].first);
	}
	if (m >= 3)
	{
		if (D[0].second == B[0].second)
		{
			if (D[1].second == B[1].second)
				ans.c = max({ans.c,
							 D[0].first + D[1].first + B[2].first,
							 D[0].first + D[2].first + B[1].first,
							 D[1].first + D[2].first + B[0].first});
			else
				ans.c = max({ans.c, D[0].first + D[1].first + B[1].first, D[1].first + D[2].first + B[0].first});
		}
		else if (D[1].second == B[0].second)
		{
			if (D[0].second == B[1].second)
				ans.c = max({ans.c, D[0].first + D[1].first + B[2].first, D[0].first + D[2].first + B[0].first});
			else
				ans.c = max({ans.c, D[0].first + D[1].first + B[1].first, D[0].first + D[2].first + B[0].first});
		}
		else
			ans.c = max(ans.c, D[0].first + D[1].first + B[0].first);
	}
	if (m >= 4)
		ans.c = max(ans.c, D[0].first + D[1].first + D[2].first + D[3].first);

	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	G.resize(n);
	int ans = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, wt;
		cin >> a >> b >> wt;
		a--;
		b--;
		G[a].emplace_back(b, wt);
		G[b].emplace_back(a, wt);
		ans += wt;
	}

	cout << 2 * ans - dfs(0).c;
}
