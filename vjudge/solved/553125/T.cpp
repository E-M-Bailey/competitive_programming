#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	const int64_t LIM = 1e15;

	unordered_map<int64_t, vector<pair<int64_t, int64_t>>> P;
	for (int n = 6; (int64_t)n * (n - 1) * (n - 2) / 6 <= LIM; n++)
	{
		__int128_t nCr = (int64_t)n * (n - 1) * (n - 2) / 6;
		for (int r = 3; nCr <= LIM && 2 * r <= n; r++, nCr = nCr * (n + 1 - r) / r)
		{
			P[(int64_t)nCr].emplace_back((int)n, r);
			if (r * 2 < n)
				P[(int64_t)nCr].emplace_back((int)n, n - r);
		}
	}

	int T;
	cin >> T;
	while (T--)
	{
		int64_t m;
		cin >> m;
		vector<pair<int64_t, int64_t>>& PP = P[m];
		if (PP.empty() || PP.back().first != m)
		{
			if (m >= 4)
			{
				int lo = 1, hi = 100'000'000;
				while (lo < hi)
				{
					int x = (lo + hi) / 2;
					int64_t n2 = (int64_t)x * (x - 1) / 2;
					if (n2 >= m)
						hi = x;
					else
						lo = x + 1;
				}
				if ((int64_t)lo * (lo - 1) / 2 == m)
				{
					PP.emplace_back(lo, 2);
					if (lo > 4)
						PP.emplace_back(lo, lo - 2);
				}
			}
			PP.emplace_back(m, 1);
			if (m > 2)
				PP.emplace_back(m, m - 1);
		}
		cout << PP.size() << '\n';
		for (auto [n, r] : PP)
			cout << '(' << n << ',' << r << ") ";
		cout << '\n';
	}
}