#include <bits/stdc++.h>

using namespace std;

const pair<int, int> DIR[]{ {0, 1}, { -1, 0 }, { 0, -1 }, { 1, 0 } };

int n, m, k;
vector<vector<char>> G, G2;
vector<char> H, H2;
vector<pair<int, int>> P;

bool dig(char c)
{
	return '0' <= c && c <= '9';
}

bool valid()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (!dig(G2[i][j]))
				continue;
			if (i == 0 || !dig(G2[i - 1][j]))
			{
				char prev = G2[i][j];
				bool inc = true, dec = true;
				for (int a = i + 1; a < n && dig(G2[a][j]); a++)
				{
					char cur = G2[a][j];
					inc &= cur >= prev;
					dec &= cur <= prev;
					prev = cur;
				}
				if (!inc && !dec)
					return false;
			}
			if (j == 0 || !dig(G2[i][j - 1]))
			{
				char prev = G2[i][j];
				bool inc = true, dec = true;
				for (int a = j + 1; a < m && dig(G2[i][a]); a++)
				{
					char cur = G2[i][a];
					inc &= cur >= prev;
					dec &= cur <= prev;
					prev = cur;
				}
				if (!inc && !dec)
					return false;
			}
		}
	return true;
}

int main()
{
	cin >> n >> m;
	G.assign(n, vector<char>(m));
	for (auto &GG : G)
		for (char &g : GG)
			cin >> g;

	cin >> k;
	H.resize(k);
	for (auto &h : H)
		cin >> h;
	sort(begin(H), end(H));

	int ans = 0;
	vector<vector<char>> best;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int d = 0; d < 4; d++)
			{
				char g0 = G[i][j];
				if (dig(g0))
					continue;
				P.clear();

				auto [di, dj] = DIR[d];
				for (int pi = i, pj = j; pi >= 0 && pi < n && pj >= 0 && pj < m; pi += di, pj += dj)
				{
					char g = G[pi][pj];
					if (g < '1' || g > '9')
						P.emplace_back(pi, pj);
				}

				for (int mask = 0; mask < (1 << k); mask++)
				{
					int ct = __builtin_popcount(mask);
					if (ct < 2 || ct >(int)P.size())
						continue;
					H2.clear();
					for (int a = 0; a < k; a++)
						if (mask & (1 << a))
							H2.push_back(H[a]);

					int val = 0, mul = 1;
					bool conn = false;
					G2 = G;
					for (int a = 0; a < ct; a++)
					{
						auto [pi, pj] = P[a];
						char g = G[pi][pj];
						int cur = H2[a] - '0';
						if (g == 'D')
							mul *= 2;
						else if (g == 'T')
							mul *= 3;
						else if (g == 'd')
							cur *= 2;
						else if (g == 't')
							cur *= 3;
						G2[pi][pj] = H2[a];
						val += cur;
						for (auto [di, dj] : DIR)
						{
							int i2 = pi + di, j2 = pj + dj;
							conn |= i2 >= 0 && i2 < n && j2 >= 0 && j2 < n && dig(G[i2][j2]);
						}
						if (a > 0)
						{
							for (int ii = pi - di, jj = pj - dj; make_pair(ii, jj) != P[a - 1]; ii -= di, jj -= dj)
								val += G[ii][jj] - '0';
						}
					}
					val *= mul;
					if (conn && val % 3 == 0 && val > ans && valid())
					{
						ans = val;
						best = G2;
					}
				}
			}
	cout << ans << '\n';
	for (auto const &row : best)
	{
		for (auto c : row)
			cout << c << ' ';
		cout << '\n';
	}
}