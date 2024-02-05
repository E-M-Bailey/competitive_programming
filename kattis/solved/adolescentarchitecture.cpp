#include <bits/stdc++.h>

using namespace std;

vector<int>			U, Y;
vector<vector<int>> DP[2];

bool f(bool cyl, int i, int j)
{
	if (i < 0 || j < 0)
		return false;
	if (i == 0 && j == 0)
		return true;

	int &dp = DP[cyl][i][j];
	if (dp >= 0)
		return dp > 0;

	if (!cyl)
	{
		if (f(false, i - 1, j))
			dp = 1;
		else if (f(true, i - 1, j) && (j == 0 || 2 * Y[j - 1] * Y[j - 1] >= U[i - 1] * U[i - 1]))
			dp = 2;
		else
			dp = 0;
	}
	else
	{
		if (f(true, i, j - 1))
			dp = 2;
		else if (f(false, i, j - 1) && (i == 0 || U[i - 1] >= 2 * Y[j - 1]))
			dp = 1;
		else
			dp = 0;
	}
	return dp;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		string c;
		int	   s;
		cin >> c >> s;
		(c == "cube" ? U : Y).push_back(s);
	}
	int u = (int)size(U), y = (int)size(Y);
	sort(begin(U), end(U), greater<int>{});
	sort(begin(Y), end(Y), greater<int>{});

	DP[0].resize(u + 1, vector<int>(y + 1, -1));
	DP[1].resize(u + 1, vector<int>(y + 1, -1));

	int	 i = u, j = y;
	bool cyl = f(true, i, j);
	if (!f(cyl, i, j))
	{
		cout << "impossible";
		return 0;
	}

	while (i || j)
	{
		cout << (cyl ? "cylinder " : "cube ") << (cyl ? Y[j - 1] : U[i - 1]) << '\n';
		bool cyl2 = DP[cyl][i][j] == 2;
		(cyl ? j : i)--;
		cyl = cyl2;
	}
}
