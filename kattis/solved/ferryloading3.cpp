#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int c;
	cin >> c;
	vector<int>			   ans;
	vector<pair<int, int>> L, R;
	ans.reserve(10000);
	L.reserve(10000);
	R.reserve(10000);
	while (c--)
	{
		int n, t, m;
		cin >> n >> t >> m;
		for (int i = 0; i < m; i++)
		{
			int	   x;
			string s;
			cin >> x >> s;
			(s == "left" ? L : R).emplace_back(x, i);
		}
		reverse(begin(L), end(L));
		reverse(begin(R), end(R));
		ans.resize(m);

		for (int tm = 0; !(L.empty() && R.empty()); tm += t, L.swap(R))
		{
			int nxt = INT_MAX;
			if (!L.empty())
				nxt = L.back().first;
			if (!R.empty())
				nxt = min(nxt, R.back().first);
			tm	   = max(nxt, tm);
			int st = max(0, (int)size(L) - n);
			while ((int)size(L) > st && L.back().first <= tm)
			{
				ans[L.back().second] = tm + t;
				L.pop_back();
			}
		}
		for (int a : ans)
			cout << a << '\n';
		cout << '\n';
	}
}
