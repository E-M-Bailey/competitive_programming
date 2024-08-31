#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<pair<int, int>> G(2 * n, {-1, -1});
	for (int i = 0; i < 2 * n; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		(G[u].first < 0 ? G[u].first : G[u].second) = v;
		(G[v].first < 0 ? G[v].first : G[v].second) = u;
	}

	vector<int> N(2 * n, -1);
	for (int i = 0; i < 2 * n; i++)
		if (N[i] < 0)
		{
			N[i] = G[i].first;
			for (int j = N[i]; j != i; j = N[j])
				N[j] = (N[G[j].first] == j ? G[j].second : G[j].first);
		}

	vector<vector<int>> cnt(n, vector<int>(n, -1));

	for (int l = 0; l < n; l++)
	{
		int incl, excl = 0;
		int lo = l, hi = l;

		int r = l;
		do
		{
			lo	 = min(lo, r);
			hi	 = max(hi, r);
			incl = (lo + 1) * (n - hi);
			excl += r * (r + 1) / 2 + (n - r - 1) * (n - r) / 2;
			cnt[l][r] = excl - n * (n + 1) / 2 + 2 * incl;
			r		  = N[N[r + n]] - n;
		}
		while (r != l);
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++)
		ans += (n + 1 - i) * i;
	ans *= n * (n + 1);

	auto const rem = [&](vector<deque<int>> &P, vector<int> &O, vector<int> &R, vector<int> &I, int &cur, int i)
	{
		int r = R[i], r2 = (int)size(P);
		P.emplace_back();
		O.push_back(0);
		if (r < 0)
		{
			for (int j = N[i]; j != i; j = N[j])
			{
				R[j] = r2;
				I[j] = (int)size(P[r2]);
				P[r2].push_back(j);
				if (j >= n)
					cur -= (j - n) * (j - n + 1) / 2 + (2 * n - j - 1) * (2 * n - j) / 2;
			}
			cur += cnt[P[r2].front() - n][P[r2].back() - n];
		}
		else
		{
			cur -= cnt[P[r].front() - n][P[r].back() - n];
			int s = (int)size(P[r]), idx = I[i] - O[r];
			if (idx >= s - idx - 1)
			{
				P[r2].assign(begin(P[r]) + idx + 1, end(P[r]));
				P[r].resize(idx);
				for (int k = 0; k < s - idx - 1; k++)
				{
					R[P[r2][k]] = r2;
					I[P[r2][k]] = k;
				}
			}
			else
			{
				P[r2].assign(begin(P[r]), begin(P[r]) + idx);
				P[r].erase(begin(P[r]), begin(P[r]) + idx + 1);
				O[r] += idx + 1;
				for (int k = 0; k < idx; k++)
				{
					R[P[r2][k]] = r2;
					I[P[r2][k]] = k;
				}
			}
			cur += cnt[P[r].front() - n][P[r].back() - n];
			cur += cnt[P[r2].front() - n][P[r2].back() - n];
		}
	};

	vector<deque<int>> P1, P2;
	vector<int>		   O1, O2, R1(2 * n, -1), R2(2 * n, -1), I1(2 * n, -1), I2(2 * n, -1);
	int				   c1 = 0, c2 = 0;
	for (int i = 0; i < n; i++)
		c1 += i * (i + 1) / 2 + (n - i - 1) * (n - i) / 2;

	for (int l = 0; l < n; l++)
	{
		P2 = P1;
		O2 = O1;
		R2 = R1;
		I2 = I1;
		c2 = c1;
		for (int r = n; r-- > l;)
		{
			ans -= c2;
			rem(P2, O2, R2, I2, c2, r);
		}
		rem(P1, O1, R1, I1, c1, l);
	}

	cout << ans / 2;
}