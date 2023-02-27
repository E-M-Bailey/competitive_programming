#include <bits/stdc++.h>

using namespace std;

struct doll
{
	int h, d, w;
};

vector<doll> D;

bool C(int i, int j)
{
	//if (i == -1 || j == -1) return true;
	const doll& a = D[i], & b = D[j];
	return a.h <= b.h - 2 * b.w && a.d <= b.d - 2 * b.w;
}

int n;
vector<vector<vector<char>>> DP;

char f(int i, int j, int m)
{
	//assert(0 <= i && i < 2 * n);
	//assert(0 <= j && j < 2 * n);
	//assert(0 <= m && m <= 2 * n);
	char& dp = DP[i][j][m];
	if (dp != -1)
		return dp;
	if (j == 2 * n - 1)
		return dp = m == n ? 3 : 0;
	if (C(i, j + 1) && f(j, j + 1, j + 1 - m))
		return dp = 1;
	if (C(j, j + 1) && f(i, j + 1, m))
		return dp = 2;
	return dp = 0;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	while (cin >> n, n)
	{
		D.resize(2 * n);
		DP.resize(2 * n);
		for (auto& DDP : DP)
		{
			DDP.resize(2 * n);
			for (auto& DDDP : DDP)
				DDDP.assign(2 * n + 1, -1);
		}
		for (auto& [h, d, w] : D)
			cin >> h >> d >> w;
		sort(begin(D), end(D), [](const doll& a, const doll& b) { return a.h < b.h; });

		for (int k = 0; k < 2 * n - 1; k++)
		{
			if (f(k, k + 1, k + 1))
			{
				vector<int> A, B;
				A.reserve(n);
				B.reserve(n);
				for (int i = 0; i <= k; i++)
					A.push_back(i);
				B.push_back(k + 1);
				int i = k, j = k + 1, m = k + 1;
				char c;
				while ((c = f(i, j, m)) != 3)
				{
					if (c == 1)
					{
						A.swap(B);
						m = j + 1 - m;
						i = j;
					}
					B.push_back(++j);
				}
				reverse(begin(A), end(A));
				reverse(begin(B), end(B));
				for (int a : A)
					cout << D[a].h << ' ' << D[a].d << ' ' << D[a].w << endl;
				cout << "-\n";
				for (int a : B)
					cout << D[a].h << ' ' << D[a].d << ' ' << D[a].w << endl;
				cout << endl;
				break;
			}
		}
	}
}