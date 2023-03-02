#include <bits/stdc++.h>

using namespace std;

struct grid
{
	int n;
	vector<vector<bool>> D, D2;
	friend istream& operator>>(istream& is, grid& g)
	{
		is >> g.n;
		g.D.assign(g.n, vector<bool>(g.n));
		g.D2.assign(g.n, vector<bool>(g.n));
		for (int i = 0; i < g.n; i++) for (int j = 0; j < g.n; j++)
		{
			char c;
			cin >> c;
			g.D[i][j] = c == '*';
		}
		return is;
	}
	void rot()
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				D2[i][j] = D[j][n - i - 1];
		D.swap(D2);
	}
	bool cont(const grid& B, int di, int dj)
	{
		for (int i = 0; i < B.n; i++)
			for (int j = 0; j < B.n; j++)
				if (!D[i + di][j + dj] && B.D[i][j]) return false;
		return true;
	}
};

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
	{
		grid A, B;
		cin >> A >> B;
		const int& n = A.n, & k = B.n;
		vector<vector<bool>> M = A.D;
		for (int r = 0; r < 4; r++, B.rot())
		{
			for (int di = 0; di <= n - k; di++)
				for (int dj = 0; dj <= n - k; dj++)
					if (A.cont(B, di, dj))
						for (int i = di; i < di + k; i++)
							for (int j = dj; j < dj + k; j++)
								M[i][j] = M[i][j] && !B.D[i - di][j - dj];
		}
		bool ans = true;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				ans &= !M[i][j];
		cout << (ans ? "YES\n" : "NO\n");
	}
}