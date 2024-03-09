#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[8]
{
	make_pair(0, 1),
	make_pair(0, -1),
	make_pair(1, 0),
	make_pair(-1, 0),
	make_pair(1, 1),
	make_pair(1, -1),
	make_pair(-1, 1),
	make_pair(-1, -1),
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int w, h;
	cin >> w >> h;
	vector<string> G(h);
	for (auto &row : G)
		cin >> row;

	vector<vector<int>> ST(h, vector<int>(w));

	queue<pair<int, int>> QA, QB;

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			if (G[i][j] == '#')
			{
				if (i == 0 || j == w - 1)
					QA.emplace(i, j);
				else if (i == h - 1 || j == 0)
					QB.emplace(i, j);
			}
			else
				ST[i][j] = -1;
		}
	ST[0][0] = ST[h - 1][w - 1] = 0;

	while (!QA.empty())
	{
		auto [i, j] = QA.front();
		QA.pop();
		if (ST[i][j] == 1)
			continue;
		ST[i][j] = 1;
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w || G[i2][j2] != '#' || ST[i2][j2] == 1)
				continue;
			QA.emplace(i2, j2);
		}
	}
	while (!QB.empty())
	{
		auto [i, j] = QB.front();
		QB.pop();
		if (ST[i][j] == 2)
			continue;
		ST[i][j] = 2;
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w || G[i2][j2] != '#' || ST[i2][j2] == 2)
				continue;
			QB.emplace(i2, j2);
		}
	}

	vector<vector<int>> D[3]
	{
		vector<vector<int>>(h, vector<int>(w, INT_MAX)),
		vector<vector<int>>(h, vector<int>(w, INT_MAX)),
		vector<vector<int>>(h, vector<int>(w, INT_MAX))
	};
	for (int k = 0; k < 3; k++)
	{
		queue<tuple<int, int, int>> Q;

		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (ST[i][j] == k)
					Q.emplace(i, j, 0);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (((i == 0 || j == w - 1) && k == 1) || ((i == h - 1 || j == 0) && k == 2))
					Q.emplace(i, j, 1);

		while (!Q.empty())
		{
			auto [i, j, d] = Q.front();
			Q.pop();
			if (D[k][i][j] < INT_MAX)
				continue;
			D[k][i][j] = d;
			for (auto [di, dj] : DIR)
			{
				int i2 = i + di, j2 = j + dj;
				if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w || D[k][i2][j2] < INT_MAX)
					continue;
				Q.emplace(i2, j2, d + 1);
			}
		}
	}

	//for (int k = 0; k < 3; k++)
	//{
	//	for (int i = 0; i < h; i++)
	//	{
	//		for (int j = 0; j < w; j++)
	//			cerr << D[k][i][j] << ' ';
	//		cerr << endl;
	//	}
	//	cerr << endl;
	//}

	tuple<int, int, int> ans{INT_MAX, -1, -1};
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
		{
			int o0 = D[0][i][j], o1 = D[1][i][j], o2 = D[2][i][j];
			if (o0 >= o1 && o1 == o2)
				ans = min(ans, make_tuple(2 * o1 - 1, i + 1 - o1, j + 1 - o1));
			if (i == 0 || j == 0)
				continue;
			int e0 = min({ D[0][i][j], D[0][i - 1][j], D[0][i][j - 1], D[0][i - 1][j - 1] });
			int e1 = min({ D[1][i][j], D[1][i - 1][j], D[1][i][j - 1], D[1][i - 1][j - 1] });
			int e2 = min({ D[2][i][j], D[2][i - 1][j], D[2][i][j - 1], D[2][i - 1][j - 1] });
			if (e0 >= e1 && e1 == e2)
				ans = min(ans, make_tuple(2 * e1, i - e1, j - e1));
		}
	auto [l, y, x] = ans;
	if (x < 0)
		cout << "Impossible";
	else
		cout << l << ' ' << x + 1 << ' ' << y + 1;
}