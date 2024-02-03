#include <bits/stdc++.h>

using namespace std;

bool find(int j, vector<vector<int>> &G, vector<int> &btoa, vector<int> &vis)
{
	if (btoa[j] == -1)
		return 1;
	vis[j] = 1;
	int di = btoa[j];
	for (int e : G[di])
		if (!vis[e] && find(e, G, btoa, vis))
		{
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsmatching(vector<vector<int>> &G, vector<int> &btoa)
{
	vector<int> vis;
	for (int i = 0; i < (int)size(G); i++)
	{
		vis.assign(size(btoa), 0);
		for (int j : G[i])
			if (find(j, G, btoa, vis))
			{
				btoa[j] = i;
				break;
			}
	}
	return (int)size(btoa) - (int)count(begin(btoa), end(btoa), -1);
}

pair<int, int> const DIR[]{
	{1, 0},
	{0, 1},
	{0, -1},
	{-1, 0},
};

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int h, w;
		cin >> h >> w;
		int					lct = 0, rct = 0;
		vector<vector<int>> C(h, vector<int>(w, -1));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				char c;
				cin >> c;
				if (c == '*')
					C[i][j] = ((i + j) % 2 ? rct : lct)++;
			}

		int ans = lct + rct;

		if (lct)
		{
			vector<vector<int>> G(lct);
			for (int i = 0; i < h; i++)
				for (int j = 0; j < w; j++)
					for (auto [di, dj] : DIR)
					{
						int i2 = i + di;
						int j2 = j + dj;
						if (i2 < 0 || i2 >= h || j2 < 0 || j2 >= w || (i + j) % 2 || C[i][j] < 0 || C[i2][j2] < 0)
							continue;
						G[C[i][j]].push_back(C[i2][j2]);
					}
			vector<int> btoa(rct, -1);
			ans -= dfsmatching(G, btoa);
		}
		cout << ans << '\n';
	}
}