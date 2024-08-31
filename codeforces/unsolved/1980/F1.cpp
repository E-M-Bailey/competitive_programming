#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n, m, k;
	cin >> n >> m >> k;
	map<int, pair<int, int>> M;
	vector<bool>			 ans(k);
	for (int i = 0; i < k; i++)
	{
		int r, c;
		cin >> r >> c;
		M[c] = max(M[c], pair{r, i});
	}
	M[m + 1]	= {n, -1};
	int		  u = 0;
	long long s = 0, pc = 1, ph = n;
	for (auto [c, ri] : M)
	{
		if (ri.first <= u)
			continue;
		if (ri.second >= 0)
			ans[ri.second] = true;
		u = max(u, ri.first);
		s += (c - pc) * ph;
		ph = n - ri.first;
		pc = c;
	}
	cout << s << '\n';
	for (bool a : ans)
		cout << a << ' ';
	cout << '\n';
}
