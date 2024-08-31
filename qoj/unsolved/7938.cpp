#include <bits/stdc++.h>

using namespace std;

int							n, m;
vector<int>					A, B, D;
vector<vector<int>>			G;
vector<array<long long, 3>> DP;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin >> n >> m;
	A.resize(n);
	B.resize(n);
	for (int i = 0; i < n; i++)
		cin >> A[i] >> B[i];

	G.resize(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	queue<int> Q;
	Q.push(0);
	D.assign(n, -1);
	D[0] = 0;
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int w : G[v])
		{
			if (D[w] >= 0)
				continue;
			D[w] = D[v] + 1;
			Q.push(w);
		}
	}

	DP.resize(n);
	vector<vector<int>> I;
	for (int v = 0; v < n; v++)
	{
		I.resize(max((int)size(I), D[v] + 1));
		I[D[v]].push_back(v);
	}

	for (int d = (int)size(I); d-- > 0;)
	{
		// +
		for (int v : I[d])
		{
			DP[v][2] = A[v] - (long long)B[v] * (d + 1);
			for (int w : G[v])
				if (D[w] == D[v] + 1)
					DP[v][2] = max(DP[v][2], DP[w][2]);
		}
		// 0
		for (int v : I[d])
		{
			DP[v][1] = A[v] - (long long)B[v] * d;
			for (int w : G[v])
				if (D[w] == D[v] + 1)
					DP[v][1] = max(DP[v][1], DP[w][1]);
				else if (D[w] == D[v])
					DP[v][1] = max(DP[v][1], DP[w][2]);
		}
		// -
		for (int v : I[d])
		{
			DP[v][0] = A[v] - (long long)B[v] * (d - 1);
			for (int w : G[v])
				if (D[w] == D[v] + 1)
					DP[v][0] = max(DP[v][0], DP[w][0]);
				else if (D[w] == D[v])
					DP[v][0] = max(DP[v][0], DP[w][1]);
		}
	}

	for (int v = 0; v < n; v++)
	{
		cerr << v + 1 << ' ' << D[v] << ' ' << DP[v][0] << ' ' << DP[v][1] << ' ' << DP[v][2] << endl;
	}

	vector<pair<int, long long>> ans;
	for (int v : G[0])
	{
		long long dp_v0 = 0;
		for (int w : G[v])
			if (D[w] == D[v] + 1)
				dp_v0 = max(dp_v0, DP[w][0]);
			else if (D[w] == D[v])
				dp_v0 = max(dp_v0, DP[w][1]);
		ans.emplace_back(v, max(DP[0][2], dp_v0));
		//ans.emplace_back(v, max(DP[0][2], DP[v][0]));
	}
	sort(begin(ans), end(ans));
	for (auto [v, a] : ans)
		cout << a << '\n';
}
