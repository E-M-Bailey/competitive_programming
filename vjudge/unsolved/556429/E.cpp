#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[4]
{
	make_pair(-1, 0),
	make_pair(0, 1),
	make_pair(1, 0),
	make_pair(0, -1),
};

int const CST[4]
{
	0, 1, 2, 1
};

struct tile
{
	bitset<4> D{};
	friend istream &operator>>(istream &is, tile &t)
	{
		static string s;
		is >> s;
		for (char c : s)
		{
			if (c == 'N')
				t.D[0] = true;
			if (c == 'E')
				t.D[1] = true;
			if (c == 'S')
				t.D[2] = true;
			if (c == 'W')
				t.D[3] = true;
		}
		return is;
	}
	bitset<4> rot(int amt)
	{
		return (D >> amt) | (D << (4 - amt));
	}
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int r, c;
	cin >> r >> c;
	int si, sj, ti, tj;
	cin >> si >> sj >> ti >> tj;

	vector<vector<tile>> GR(r, vector<tile>(c));
	for (auto &row : GR)
		for (auto &t : row)
			cin >> t;

	vector<vector<vector<vector<tuple<int, int, int, int, int>>>>> G(r,
		vector<vector<vector<tuple<int, int, int, int, int>>>>(c,
			vector<vector<tuple<int, int, int, int, int>>>(4)));


	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			for (int r = 0; r < 4; r++)
			{
				bitset<4> conn = GR[i][j].rot(r);
				G[i][j][r].emplace_back(i, j, (r + 1) % 4, 1, 0);
				G[i][j][r].emplace_back(i, j, (r + 3) % 4, 1, 0);

				for (int d = 0; d < 4; d++)
				{
					auto [di, dj] = DIR[d];
					int i2 = i + di, j2 = j + dj;
					if (i2 < 0 || i2 >= r || j2 < 0 || j2 >= c || !conn[d])
						continue;
					for (int r2 = 0; r2 < 4; r2++)
					{
						bitset<4> conn2 = GR[i2][j2].rot(r2);
						if (!conn2[(d + 2) % 4])
							continue;
						G[i][j][r].emplace_back(i2, j2, r2, 0, CST[r2]);
					}
				}
			}
		}
}