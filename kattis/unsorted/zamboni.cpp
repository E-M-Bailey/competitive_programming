#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int64_t r, c, i, j;
	int64_t n;
	while (cin >> r >> c >> i >> j >> n)
	{
		i--;
		j--;
		int64_t oi = i, oj = j;
		vector<vector<char>> G(r, vector<char>(c, '.'));
		int64_t N = lcm(lcm(4 * r, 4 * c), 26);
		for (int64_t t = 1; t <= min(n, max(r, c)); t++)
		{
			switch (t % 4)
			{
			case 0:
			{
				int64_t j2 = j - t;
				for (int64_t k = j; k > j2; k--)
				{
					int64_t l = k % c;
					if (l < 0)
						l += c;
					G[i][l] = (t + 25) % 26 + 'A';
				}
				j = (j2 % c + c) % c;
				break;
			}
			case 1:
			{
				int64_t i2 = i - t;
				for (int64_t k = i; k > i2; k--)
				{
					int64_t l = k % r;
					if (l < 0)
						l += r;
					G[l][j] = (t + 25) % 26 + 'A';
				}
				i = (i2 % r + r) % r;
				break;
			}
			case 2:
			{
				int64_t j3 = j + t;
				for (int64_t k = j; k < j3; k++)
					G[i][k % c] = (t + 25) % 26 + 'A';
				j = j3 % c;
				break;
			}
			case 3:
			{
				int64_t i3 = i + t;
				for (int64_t k = i; k < i3; k++)
					G[k % r][j] = (t + 25) % 26 + 'A';
				i = i3 % r;
				break;
			}
			}
		}

		/*
		vector<pair<int64_t, int64_t>> pos(N);
		for (int64_t t = 0; t < N; t++)
		{
			pos[t] = {i, j};
			switch (t % 4)
			{
			case 0:
				j = (j - t) % c;
				if (j < 0)
					j += c;
				break;
			case 1:
				i = (i - t) % r;
				if (i < 0)
					i += r;
				break;
			case 2:
				j = (j + t) % c;
				break;
			case 3:
				i = (i + t) % r;
				break;
			}
		}
		*/
		auto const pos = [i = oi, j = oj, r, c](int64_t t) -> pair<int64_t, int64_t>
		{
			int64_t row = (t % 4 == 1 || t % 4 == 2) ? -((t + 1) / 2) : (t + 1) / 2;
			row = (i + row) % r;
			if (row < 0)
				row += r;

			int64_t col = (t % 4 <= 1) ? -(t / 2) : t / 2 + 1;
			col = (j + col) % c;
			if (col < 0)
				col += c;
			// std::cerr << j << ' ' << t << ' ' << col << std::endl;
			return {row, col};
		};

		vector<pair<char, int64_t>> R(r), C(c);
		int64_t ts = max(n - N, min(n, max(r, c)) + 1);
		tie(i, j) = pos(ts);
		for (int64_t t = ts, tc = t % c, tr = t % r, t26 = (t + 25) % 26; t <= n; t++)
		{
			//cerr << t << ' ' << i << ' ' << j << endl;
			if (t % 2 == 0)
			{
				R[i] = {t26 + 'A', t};
			}
			else
			{
				C[j] = {t26 + 'A', t};
			}

			if (++tc == c)
				tc -= c;
			if (++tr == r)
				tr -= r;
			switch ((t + 1) % 4)
			{
			case 0:
				j = j - tc;
				if (j < 0)
					j += c;
				break;
			case 1:
				i = i - tr;
				if (i < 0)
					i += r;
				break;
			case 2:
				j = j + tc;
				if (j >= c)
					j -= c;
				break;
			case 3:
				i = i + tr;
				if (i >= r)
					i -= r;
				break;
			}

			if (++t26 == 26)
				t26 = 0;
		}
		// for (auto [ch, t] : C)
		//	cerr << ch << ' ' << t << endl;

		auto [ii, jj] = pos(n);
		G[ii][jj] = '@';

		for (int a = 0; a < r; a++)
		{
			for (int b = 0; b < c; b++)
			{
				char c = G[a][b];
				if (c != '@')
				{
					int64_t tt = 0;
					if (R[a].second > 0)
						tie(c, tt) = R[a];
					if (C[b].second > tt)
						c = C[b].first;
				}
				cout << c;
			}
			cout << '\n';
		}
		cout << flush;
	}
}