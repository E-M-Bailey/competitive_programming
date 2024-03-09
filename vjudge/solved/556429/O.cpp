#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[4]{
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	long long n, s;
	cin >> n >> s;
	vector<vector<char>> G(n, vector<char>(n));

	int si, sj, ti, tj;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			char &g = G[i][j];
			cin >> g;
			if (g == 'M')
				tie(si, sj) = tie(i, j);
			else if (g == 'D')
				tie(ti, tj) = tie(i, j);
		}

	vector<vector<long long>> DB(n, vector<long long>(n)), DM(n, vector<long long>(n));
	queue<pair<int, int>> Q;

	for (auto &DD : DB)
		fill(begin(DD), end(DD), INT_MAX);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (G[i][j] == 'H')
			{
				Q.emplace(i, j);
				DB[i][j] = 0;
			}

	while (!Q.empty())
	{
		auto [i, j] = Q.front();
		Q.pop();
		long long d = DB[i][j];
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= n)
				continue;
			long long &d2 = DB[i2][j2];
			char g = G[i2][j2];
			if (d2 != INT_MAX || g == 'T' || g == 'D')
				continue;
			d2 = d + s;
			Q.emplace(i2, j2);
		}
	}

	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		cerr << setw(5) << (DB[i][j] == INT_MAX ? -1 : DB[i][j]);
	//	cerr << endl;
	//}
	//cerr << endl;

	const auto works = [&](long long x)
	{
		x *= s;
		if (DB[si][sj] <= x)
			return false;

		for (auto &DD : DM)
			fill(begin(DD), end(DD), INT_MAX);
		Q.emplace(si, sj);
		DM[si][sj] = x;

		while (!Q.empty())
		{
			auto [i, j] = Q.front();
			Q.pop();
			long long d = DM[i][j];
			for (auto [di, dj] : DIR)
			{
				int i2 = i + di, j2 = j + dj;
				if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= n)
					continue;
				long long &d2 = DM[i2][j2];
				char g = G[i2][j2];
				if (d2 != INT_MAX || DB[i2][j2] <= d + 1 || g == 'T')
					continue;
				d2 = d + 1;
				Q.emplace(i2, j2);
			}
		}
		//cerr << x << ":\n";
		//for (int i = 0; i < n; i++)
		//{
		//	for (int j = 0; j < n; j++)
		//		cerr << setw(5) << (DM[i][j] == INT_MAX ? -1 : DM[i][j]);
		//	cerr << endl;
		//}
		//cerr << endl;
		return DM[ti][tj] != INT_MAX;
	};

	if (!works(0))
	{
		cout << -1;
		return 0;
	}

	long long lo = 0, hi = n * n;
	while (lo < hi)
	{
		long long x = (lo + hi + 1) / 2;

		if (works(x))
			lo = x;
		else
			hi = x - 1;
	}

	cout << (lo + hi) / 2;
}