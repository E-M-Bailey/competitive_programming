#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<string> S(n);
	for (auto &s : S)
		cin >> s;
	int ans[5]{};
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
		{
			int a = 0, b = 0;
			for (int ii : {i - 1, i})
				for (int jj : {j - 1, j})
				{
					a += S[ii][jj] == 'X';
					b += S[ii][jj] == '#';
				}
			if (b == 0)
				ans[a]++;
		}
	for (int aa : ans)
		cout << aa << '\n';
}
