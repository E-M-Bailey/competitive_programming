#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[]{
	make_pair(1, 2),
	make_pair(-1, 2),
	make_pair(1, -2),
	make_pair(-1, -2),
	make_pair(2, 1),
	make_pair(2, -1),
	make_pair(-2, 1),
	make_pair(-2, -1)
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int r, c, gr, gc, lr, lc;
	while (cin >> r >> c >> gr >> gc >> lr >> lc)
	{
		gr--;
		gc--;
		lr--;
		lc--;
		vector<vector<int>> G(r * c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				for (auto [di, dj] : DIR)
				{
					int ii = i + di, jj = j + dj;
					if (ii < 0 || ii >= r || jj < 0 || jj >= c)
						continue;
					G[i * c + j].push_back(ii * c + jj);
					G[ii * c + jj].push_back(i * c + j);
				}
			}
		}

		vector<int> D(r * c, -1);
		queue<pair<int, int>> Q;
		Q.emplace(gr * c + gc, 0);
		while (!Q.empty())
		{
			auto [v, d] = Q.front();
			Q.pop();
			if (D[v] >= 0)
				continue;
			D[v] = d;
			for (int w : G[v])
				if (D[w] < 0)
					Q.emplace(w, d + 1);
		}
		if (D[lr * c + lc] < 0)
			cout << "impossible\n";
		else
			cout << D[lr * c + lc] << '\n';
	}
}