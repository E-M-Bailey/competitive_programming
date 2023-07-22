#include <bits/stdc++.h>

using namespace std;

constexpr array<bool, 127> allowed()
{
	array<bool, 127> ans{};
	for (int c = 'A'; c <= 'Z'; c++)
		ans[c] = ans[c | 32] = 1;
	for (int c = '0'; c <= '9'; c++)
		ans[c] = 1;
	ans['?'] = ans['!'] = ans[','] = ans['.'] = ans[' '] = ans['+'] = 1;
	return ans;
}
array<bool, 127> constexpr AL = allowed();

int h, w;
vector<string> G;

struct rect
{
	int i1, j1, i2, j2, a;
	friend bool operator<(rect const &a, rect const &b)
	{
		return a.a < b.a;
	}
	bool contains(int i, int j) const
	{
		return i1 <= i && i <= i2 && j1 <= j && j <= j2;
	}
};

int main()
{
	cin >> h >> w;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	G.resize(h);
	for (string &row : G)
		getline(cin, row);

	vector<rect> R;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (G[i][j] == '+' && (i == 0 || G[i - 1][j] != '+') && (j == 0 || G[i][j - 1] != '+'))
			{
				int i2 = i, j2 = j;
				while (i2 < h && G[i2][j] == '+')
					i2++;
				i2--;
				while (j2 < w && G[i][j2] == '+')
					j2++;
				j2--;
				R.push_back({ i, j, i2, j2, (i2 - i + 1) * (j2 - j + 1) });
			}
	sort(begin(R), end(R));

	vector<rect> D;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (!AL[G[i][j]])
				for (rect const &r : R)
					if (r.contains(i, j))
					{
						D.push_back(r);
						break;
					}

	for (rect const &r : D)
		for (int i = r.i1; i <= r.i2; i++)
			for (int j = r.j1; j <= r.j2; j++)
				G[i][j] = ' ';

	for (string const &row : G)
		cout << row << '\n';
}
