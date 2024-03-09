#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> W, V, D;
vector<vector<int>> CH;
vector<vector<pair<int64_t, int>>> DP;

void dfs(int v, int64_t lam)
{
	for (int w : CH[v])
		dfs(w, lam);
	int64_t cv = 0;
	for (int anc = v;; cv += D[anc] * W[v], anc = V[anc])
	{
		int idx = anc < 0 ? 0 : anc;
		auto &dp = DP[v][idx];

		// Sawmill
		dp.first = lam;
		dp.second = 1;
		for (int w : CH[v])
		{
			dp.first += DP[w][v].first;
			dp.second += DP[w][v].second;
		}

		// No sawmill
		if (anc != v)
		{
			pair<int64_t, int> no{cv, 0};
			for (int w : CH[v])
			{
				no.first += DP[w][idx].first;
				no.second += DP[w][idx].second;
			}
			dp = min(dp, no);
		}
		if (anc < 0)
			break;
	}
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int k;
	cin >> n >> k;
	n++;
	W.resize(n);
	V.resize(n);
	D.resize(n);
	CH.resize(n);
	for (int i = 1; i < n; i++)
	{
		cin >> W[i] >> V[i] >> D[i];
		CH[V[i]].push_back(i);
	}
	V[0] = -1;
	DP.resize(n, vector<pair<int64_t, int>>(n));

	int64_t lo = 0, hi = 2e9;
	int64_t ans;
	while (lo < hi)
	{
		int64_t lam = (lo + hi) / 2;
		dfs(0, lam);
		auto [c, ct] = DP[0][0];
		if (ct > k)
			lo = lam + 1;
		else
		{
			hi = lam;
			ans = c - lam * k;
		}
	}
	cout << ans;
}
/*
int n;
vector<int> W, V, D;
vector<vector<int>> CH;
vector<vector<vector<int64_t>>> DP;

vector<int64_t> conv(vector<int64_t> const &a, vector<int64_t> const &b)
{
	vector<int64_t> ans(a.size() + b.size() - 1, INT_MAX);
	for (int i = 0; i < (int)a.size(); i++)
		for (int j = 0; j < (int)b.size(); j++)
			ans[i + j] = min(a[i] + b[j], ans[i + j]);
	return ans;
}

vector<int64_t> &dfs(int v, int anc)
{
	vector<int64_t> &dp = DP[v][anc < 0 ? 0 : anc];
	if (dp.empty())
	{
		int64_t cv = 0;
		for (int w = v; w != anc; w = V[w])
		{
			cv += D[w];
			//cerr << v << ' ' << w << ' ' << anc << endl;
		}
		cv *= W[v];

		dp.push_back(0);

		// Sawmill
		for (int w : CH[v])
			dp = conv(dp, dfs(w, v));
		dp.insert(dp.begin(), INT_MAX);

		// No sawmill
		if (anc != v)
		{
			vector<int64_t> no{cv};
			for (int w : CH[v])
				no = conv(no, dfs(w, anc));
			dp.resize(max(dp.size(), no.size()), INT_MAX);
			for (int i = 0; i < (int)no.size(); i++)
				dp[i] = min(dp[i], no[i]);
		}
	}

	//cerr << v << ' ' << anc << endl;
	//for (auto d : dp)
	//	cerr << ' ' << d;
	//cerr << endl;

	return dp;
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int k;
	cin >> n >> k;
	n++;
	W.resize(n);
	V.resize(n);
	D.resize(n);
	CH.resize(n);
	for (int i = 1; i < n; i++)
	{
		cin >> W[i] >> V[i] >> D[i];
		CH[V[i]].push_back(i);
	}
	V[0] = -1;

	DP.resize(n, vector<vector<int64_t>>(n));

	auto ans = dfs(0, -1)[k];
	cout << ans;
}
*/