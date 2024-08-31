#include <bits/stdc++.h>

using namespace std;

const long long mod = 998244353;

long long modpow(long long b, long long e)
{
	long long ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1)
			ans = ans * b % mod;
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int T;
	cin >> T;
	while (T--)
	{
		int n, m;
		cin >> n >> m;
		vector<int>			   X;
		vector<pair<int, int>> E(m);
		for (auto &[a, b] : E)
		{
			cin >> a >> b;
			b++;
			X.push_back(a);
			X.push_back(b);
		}

		sort(begin(X), end(X));
		X.erase(unique(begin(X), end(X)), end(X));
		n = (int)size(X);

		vector<vector<int>> G(n);
		for (auto &[a, b] : E)
		{
			a = int(lower_bound(begin(X), end(X), a) - begin(X));
			b = int(lower_bound(begin(X), end(X), b) - begin(X));
			G[a].push_back(b);
		}

		long long			bestn = 1, bestd = 1;
		vector<vector<long long>> L1(n, vector<long long>(n)), L2(n, vector<long long>(n));

		for (int r = n; r-- > 0;)
		{
			L1[r][r] = L2[r][r] = 0;
			for (int l = r; l-- > 0;)
			{
				L1[l][r] = LLONG_MAX / 2;
				L2[l][r] = LLONG_MIN / 2;
				for (int b : G[l])
					if (b <= r)
					{
						L1[l][r] = min(L1[l][r], L1[b][r] + 1);
						L2[l][r] = max(L2[l][r], L2[b][r] + 1);
					}
				// cerr << l << ' ' << r << ' ' << L1[l][r] << ' ' << L2[l][r] << endl;
				if (L2[l][r] > 0 && L2[l][r] * bestd > L1[l][r] * bestn)
				{
					bestn = L2[l][r];
					bestd = L1[l][r];
				}
			}
		}

		long long best = bestn * modpow(bestd, mod - 2) % mod;
		cout << best << '\n';
		cerr << endl;
	}
}
