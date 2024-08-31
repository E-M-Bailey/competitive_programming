#include <bits/stdc++.h>

using namespace std;

int					n, s, t;
vector<int>			P;
vector<vector<int>> C;
vector<int>			D;
vector<int>			path;

vector<long double> DP;

long double dfs(int v)
{
	if (DP[v] < 0)
	{
		DP[v] = 0;
		if (size(C[v]) + (v == s && path.front() == t) != 0)
		{
			for (int w : C[v])
				DP[v] += dfs(w);
			DP[v] /= size(C[v]) + (v == s && path.front() == t);
			DP[v] += 1;
		}
		if (v == t && path.front() == t)
		{
			C[s].push_back(t);
			long double p = 1;
			for (int u : path)
				p /= size(C[u]);
			int l = (int)size(path);
			DP[v] = (DP[v] - p * l) / (1 - p) + l * p / (1 - p);
		}
	}
	return DP[v];
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n >> s >> t;
		s--;
		t--;
		DP.assign(n, -1);
		P.assign(n, 0);
		C.assign(n, {});
		D.assign(n, 0);
		for (int i = 1; i < n; i++)
		{
			cin >> P[i];
			P[i]--;
			C[P[i]].push_back(i);
		}

		path.clear();
		path.push_back(s);
		while (path.back() != t && path.back() != 0)
			path.push_back(P[path.back()]);
		reverse(begin(path), end(path));

		// mt19937_64 randy(1320487130948ll);
		// C[s].push_back(t);
		// long double ans = 0;
		// long double a = 0, b = 0;
		// for (int i = 0; i < 10000000; i++)
		// {
		// 	int v = 0;
		// 	int ca = 0, cb = 0;
		// 	while (!C[v].empty())
		// 	{
		// 		uniform_int_distribution<int> distr(0, (int)size(C[v]) - 1);
		// 		int w = C[v][distr(randy)];
		// 		ans++;
		// 		ca++;
		// 		if (v == s && w == t && path.front() == t)
		// 		{
		// 			ca -= (int)size(path);
		// 			cb += (int)size(path);
		// 		}
		// 		v = w;
		// 	}
		// 	a += ca;
		// 	b += cb;
		// }
		// cout << fixed << setprecision(13) << ans / 10000000 << ' ' << a / 10000000 << ' ' << b / 10000000 << '\n';
		// C[s].pop_back();

		if (path.front() != t)
			C[s].push_back(t);
		cout << fixed << setprecision(13) << dfs(0) << '\n';
	}
}
