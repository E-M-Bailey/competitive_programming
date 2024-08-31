#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> by_bits(int n, int k)
{
	vector<int> ans;
	for (int i = 0; i < (1 << n); i++)
		if (__builtin_popcount(i) == k)
			ans.push_back(i);
	return ans;
}

pair<int, vector<vector<bool>>> solve(int n, int l)
{
	vector<vector<int>> 

	int			l = 0;
	while ((int)size(ids = by_bits(l, l / 2)) < n)
		l++;

	vector<vector<bool>> ans(l + 2 - (l % 2), vector<bool>(n));

	for (int i = 0; i < l; i++)
		for (int j = 0; j < n; j++)
			ans[i][j] = ids[j] & (1 << i);
	ans[l].assign(n, true);

	return ans;
}

int main()
{
	int n, w;
	cin >> n >> w;
	
	auto plan = solve(n);
	if ((int)size(plan) > w)
	{
		cout << "infinity";
		return 0;
	}

	cout << size(plan) << '\n';
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < n; j++)
			cout << char('1' + plan[i % (int)size(plan)][j]);
		cout << '\n';
	}
}
