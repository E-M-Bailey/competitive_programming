#include <bits/stdc++.h>

using namespace std;

typedef long double F;
const F INF = numeric_limits<F>::infinity();

struct tile
{
	map<int, int> L, R;
};

F lerp(const map<int, int>& A, int y)
{
	auto a = prev(A.upper_bound(y)), b = A.lower_bound(y);
	if (a == b)
		return a->second;
	F f = F(y - a->first) / (b->first - a->first);
	return (1 - f) * a->second + f * b->second;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;

	vector<pair<int, int>> P;

	vector<tile> T(n);
	for (auto& [L, R] : T)
	{
		int k;
		cin >> k;
		P.resize(k);
		int mx = 0;
		//int Mx = 0;
		for (auto& [x, y] : P)
		{
			cin >> x >> y;
			mx = min(mx, x);
			//Mx = max(Mx, x);
		}
		//w = Mx - mx;
		for (auto& [x, y] : P)
			x -= mx;
		bool l = true;
		L.emplace(0, -mx);
		int py = 0;
		for (int i = 1; i < k; i++)
		{
			auto [x, y] = P[i];
			l ^= y == py;
			(l ? L : R).emplace(y, x);
			py = y;
		}
	}

	vector<vector<F>> D(n, vector<F>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			const map<int, int>& A = T[i].R, & B = T[j].L;
			for (auto [y, x] : A)
				D[i][j] = max(D[i][j], x - lerp(B, y));
			for (auto [y, x] : B)
				D[i][j] = max(D[i][j], lerp(A, y) - x);
		}

	vector<vector<F>> DP(n, vector<F>(1 << n));
	for (int a = 0; a < n; a++)
		for (auto [y, x] : T[a].R)
			DP[a][0] = max(DP[a][0], (F)x);

	for (int ct = 1; ct < n; ct++)
		for (int mask = 0; mask < 1 << n; mask++)
		{
			if (__builtin_popcount(mask) != ct)
				continue;
			for (int a = 0; a < n; a++)
			{
				if ((1 << a) & mask)
					continue;
				DP[a][mask] = INF;
				for (int b = 0; b < n; b++)
				{
					if (b == a || ((1 << b) & ~mask))
						continue;
					DP[a][mask] = min(DP[a][mask], D[a][b] + DP[b][mask ^ (1 << b)]);
				}
			}
		}

	F ans = INF;
	for (int a = 0; a < n; a++)
		ans = min(ans, DP[a][(1 << n) - 1 - (1 << a)]);
	cout << fixed << setprecision(3) << ans;
}