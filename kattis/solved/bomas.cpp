#include <bits/stdc++.h>

using namespace std;

typedef double		db;
typedef complex<db> cd;

int n, q, N;

vector<pair<cd, db>> C;
vector<int>			 P;
vector<vector<int>>	 CH;

db eval(pair<int, bool> a, db x)
{
	db dx = x - real(C[a.first].first);
	db r  = C[a.first].second;
	db dy = (a.second ? 1 : -1) * sqrt(max(0., r * r - dx * dx));
	return dy + imag(C[a.first].first);
}
auto const cmp_y = [](pair<int, bool> a, pair<int, bool> b)
{
	db x = max(real(C[a.first].first) - C[a.first].second, real(C[b.first].first) - C[b.first].second);
	return tuple{eval(a, x), a.second, a.first} < tuple{eval(b, x), b.second, b.first};
};
bool cont(int i, int j)
{
	db r = max(C[i].second, C[j].second);
	return norm(C[i].first - C[j].first) < r * r;
}
vector<tuple<db, int, bool>>		  E;
set<pair<int, bool>, decltype(cmp_y)> S;
vector<decltype(S)::iterator>		  SI;

vector<pair<int, int>> DP;
void				   dfs(int v)
{
	for (int w : CH[v])
		dfs(w);
	if (v <= n)
	{
		for (int w : CH[v])
		{
			DP[v].first += DP[w].second;
			DP[v].second += DP[w].first;
		}
		DP[v].second = max(DP[v].second + 1, DP[v].first);
	}
	else
		for (int w : CH[v])
		{
			DP[v].first += DP[w].first;
			DP[v].second += DP[w].second;
		}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> q;
	C.resize(N = n + q + 1);
	C[0].second = 1e8;
	for (int i = 1; i <= n + q; i++)
	{
		db x, y, r;
		cin >> x >> y >> r;
		C[i] = {cd{x, y}, r};
	}
	P.resize(N);
	CH.resize(N);
	E.resize(N * 2);
	SI.resize(N * 2);
	for (int i = 0; i < N; i++)
	{
		auto [xy, r] = C[i];
		db x		 = real(xy);
		E[i * 2]	 = {x - r, i, true};
		E[i * 2 + 1] = {x + r, i, false};
	}
	sort(begin(E), end(E));

	for (auto [x, i, s] : E)
	{
		if (s)
		{
			SI[i * 2]	  = S.emplace(i, true).first;
			SI[i * 2 + 1] = S.emplace(i, false).first;
			if (i != 0)
			{
				int j = next(SI[i * 2])->first;
				if (!cont(j, i))
					j = P[j];
				CH[j].push_back(i);
				P[i] = j;
			}
		}
		else
		{
			S.erase(SI[i * 2]);
			S.erase(SI[i * 2 + 1]);
		}
	}

	DP.resize(N);
	dfs(0);

	for (int i = n + 1; i < N; i++)
		cout << max(DP[i].first + 1, DP[i].second) << '\n';
}
