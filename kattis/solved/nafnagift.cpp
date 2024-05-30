#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s, t;
	getline(cin, s);
	getline(cin, t); 
	int					n = (int)size(s), m = (int)size(t);
	vector<vector<int>> DP(n + 1, vector<int>(m + 1));
	for (int i = 0; i <= n; i++)
		DP[i][0] = i;
	for (int j = 0; j <= m; j++)
		DP[0][j] = j;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			DP[i][j] = 1 + (s[i - 1] == t[j - 1] ? DP[i - 1][j - 1] : min(DP[i - 1][j], DP[i][j - 1]));
	int	   i = n, j = m;
	string ans;
	while (i && j)
	{
		if (s[i - 1] == t[j - 1])
		{
			ans += s[i - 1];
			i--;
			j--;
		}
		else if (DP[i - 1][j] <= DP[i][j - 1])
		{
			ans += s[i - 1];
			i--;
		}
		else
		{
			ans += t[j - 1];
			j--;
		}
	}
	while (i)
		ans += s[--i];
	while (j)
		ans += t[--j];
	reverse(begin(ans), end(ans));
	cout << ans;
}
