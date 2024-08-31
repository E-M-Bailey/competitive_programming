#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin.tie(0)->sync_with_stdio(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		go();
	}
}

pair<int, int> constexpr DIR[4]{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void go()
{
	int n;
	cin >> n;
	vector<string> G(2);
	cin >> G[0] >> G[1];
	vector<vector<bool>> V(2, vector<bool>(n));
	V[0][0] = true;
	queue<pair<int, int>> Q;
	Q.emplace(0, 0);

	while (!Q.empty())
	{
		auto [i, j] = Q.front();
		Q.pop();
		for (auto [di, dj] : DIR)
		{
			int i2 = di + i, j2 = dj + j;
			if (i2 < 0 || i2 >= 2 || j2 < 0 || j2 >= n)
				continue;
			auto [di2, dj2] = DIR[G[i2][j2] == '<' ? 2 : 3];
			int i3 = di2 + i2, j3 = dj2 + j2;
			if (V[i3][j3])
				continue;
			Q.emplace(i3, j3);
			V[i3][j3] = true;
		}
	}

	cout << (V[1][n - 1] ? "YES\n" : "NO\n");
}
