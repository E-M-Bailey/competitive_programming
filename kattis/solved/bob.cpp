#include <bits/stdc++.h>

using namespace std;

int					n, m;
vector<vector<int>> G;
vector<vector<int>> W;

struct col
{
	int					   val = 0;
	int64_t				   A;
	vector<pair<int, int>> S;

	void add(int v, int w)
	{
		if (v != val)
		{
			val = v;
			S.clear();
			A = 0;
		}
		int h = 1;
		while (!S.empty() && S.back().first >= w)
		{
			auto [sw, sh] = S.back();
			S.pop_back();
			A -= sw * sh;
			h += sh;
		}
		S.emplace_back(w, h);
		A += w * h;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	G.resize(n, vector<int>(m));
	for (auto &GG : G)
		for (int &g : GG)
			cin >> g;
	W.resize(n, vector<int>(m, 1));
	for (int i = 0; i < n; i++)
		for (int j = 1; j < m; j++)
			if (G[i][j] == G[i][j - 1])
				W[i][j] = W[i][j - 1] + 1;
	vector<col> C(m);
	int64_t		ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			C[j].add(G[i][j], W[i][j]);
			ans += C[j].A;
		}
	cout << ans;
}
