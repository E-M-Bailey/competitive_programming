#include <bits/stdc++.h>

using namespace std;

/*
pair<int, vector<int>> hungarian(const vector<vector<int>> &a)
{
	if (a.empty())
		return { 0, {} };
	int n = (int)a.size() + 1, m = (int)a[0].size() + 1;
	vector<int> u(n), v(m), p(m), ans(n - 1);
	for (int i = 1; i < n; i++)
	{
		p[0] = i;
		int j0 = 0;
		vector<int> dist(m, INT_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do
		{
			done[j0] = true;
			int i0 = p[j0], j1, delta = INT_MAX;
			for (int j = 1; j < m; j++)
				if (!done[j])
				{
					auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
					if (cur < dist[j])
					{
						dist[j] = cur;
						pre[j] = j0;
					}
					if (dist[j] < delta)
					{
						delta = dist[j];
						j1 = j;
					}
				}
			for (int j = 0; j < m; j++)
			{
				if (done[j])
				{
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else
					dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0)
		{
			int j1 = pre[j0];
			p[j0] = p[j1];
			j0 = j1;
		}
	}
	for (int j = 1; j < m; j++)
		if (p[j])
			ans[p[j] - 1] = j - 1;
	return { -v[0], ans };
}
*/

typedef vector<int> vi;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define sz(a) ((int)size(a))
pair<int, vi> hungarian(const vector<vi> &a)
{
	if (a.empty()) return { 0, {} };
	int n = sz(a) + 1, m = sz(a[0]) + 1;
	vi u(n), v(m), p(m), ans(n - 1);
	rep(i, 1, n)
	{
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vi dist(m, INT_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do
		{ // di jkstra
			done[j0] = true;
			int i0 = p[j0], j1, delta = INT_MAX;
			rep(j, 1, m) if (!done[j])
			{
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			rep(j, 0, m)
			{
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0)
		{ // update alternating path
			int j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
	return { -v[0], ans }; // min cost
}

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> A1(n, vector<int>(n)), B1 = A1, A2 = A1, B2 = A1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> A1[i][j] >> B1[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> A2[i][j] >> B2[i][j];

	int best = INT_MAX, bestca;
	vector<int> best1, best2;
	for (int ca = 0; ca <= n; ca++)
	{
		auto [c1, m1] = hungarian(A1);
		auto [c2, m2] = hungarian(A2);
		// for (int i = 0; i < n; i++)
		// {
		// 	for (int j = 0; j < n; j++)
		// 		cerr << ' ' << B1[i][j];
		// 	cerr << endl;
		// }
		// for (int i = 0; i < n; i++)
		// {
		// 	for (int j = 0; j < n; j++)
		// 		cerr << ' ' << B2[i][j];
		// 	cerr << endl;
		// }
		// cerr << c1 << ' ' << c2 << ' ' << c1 + c2 << endl;
		if (c1 + c2 < best)
		{
			best = c1 + c2;
			bestca = ca;
			best1 = move(m1);
			best2 = move(m2);
		}
		if (ca < n)
		{
			A1[ca].swap(B1[ca]);
			A2[ca].swap(B2[ca]);
		}
	}

	vector<int> inv2(n);
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		inv2[best2[i]] = i;
		ans += (best1[i] < bestca ? B1 : A1)[i][best1[i]];
		ans += (best2[i] < bestca ? B2 : A2)[i][best2[i]];
	}


	cout << ans << '\n';
	for (int i = 0; i < n; i++)
		cout << i + 1 << ' ' << best1[i] + 1 << (best1[i] < bestca ? 'A' : 'B') << ' ' << inv2[best1[i]] + 1 << '\n';
}