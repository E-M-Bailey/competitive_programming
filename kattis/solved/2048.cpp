#include <bits/stdc++.h>
using namespace std;

void rot(array<array<int, 4>, 4> &G)
{
	static array<array<int, 4>, 4> G2;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			G2[3 - j][i] = G[i][j];
	G = G2;
}

int main()
{
	array<array<int, 4>, 4> G;
	for (auto &GG : G)
		for (int &g : GG)
			cin >> g;
	int r;
	cin >> r;

	for (int i = 0; i < r; i++)
		rot(G);

	vector<int> S;
	for (int i = 0; i < 4; i++)
	{
		S.clear();
		bool rp = false;
		for (int g : G[i])
		{
			if (g == 0)
				continue;
			if (!rp && size(S) && g == S.back())
			{
				S.back() = g * 2;
				rp		 = true;
			}
			else
			{
				S.push_back(g);
				rp = false;
			}
		}
		S.resize(4);
		copy_n(begin(S), 4, begin(G[i]));
	}

	for (int i = r; i < 4; i++)
		rot(G);

	for (const auto &GG : G)
	{
		for (int g : GG)
			cout << g << ' ';
		cout << '\n';
	}
}
