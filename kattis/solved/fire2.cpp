#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int t;
	cin >> t;
	while (t--)
	{
		int w, h;
		cin >> w >> h;
		vector<string> GR(h);
		for (string &row : GR)
			cin >> row;

		vector<bool> D(w * h), E(w * h), F(w * h);
		vector<int> A, B, C;
		vector<vector<int>> G(w * h);
		for (int i = 0, idx = 0; i < h; i++)
			for (int j = 0; j < w; j++, idx++)
			{
				char c = GR[i][j];
				if (c == '#')
					continue;
				D[idx] = i == 0 || i == h - 1 || j == 0 || j == w - 1;
				if (c == '@')
				{
					E[idx] = true;
					A.push_back(idx);
				}
				if (c == '*')
				{
					F[idx] = true;
					B.push_back(idx);
				}
				if (i > 0)
				{
					char d = GR[i - 1][j];
					if (d != '#')
					{
						G[idx - w].push_back(idx);
						G[idx].push_back(idx - w);
					}
				}
				if (j > 0)
				{
					char d = GR[i][j - 1];
					if (d != '#')
					{
						G[idx - 1].push_back(idx);
						G[idx].push_back(idx - 1);
					}
				}
			}

		bool esc = D[A[0]];
		int tim = 1;
		while (!esc && !A.empty())
		{
			tim++;
			C.clear();
			for (int u : B)
				for (int v : G[u])
					if (!F[v])
					{
						F[v] = true;
						C.push_back(v);
					}
			C.swap(B);
			C.clear();
			for (int u : A)
			{
				for (int v : G[u])
					if (!E[v] && !F[v])
					{
						esc |= D[v];
						E[v] = true;
						C.push_back(v);
					}
			}
			C.swap(A);
		}
		if (esc)
			cout << tim << '\n';
		else
			cout << "IMPOSSIBLE\n";
	}
}