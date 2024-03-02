#include <bits/stdc++.h>

using namespace std;

int cost(unordered_set<int> const &P, unordered_set<int> const &Q, int sz)
{
	int ans = (int)(size(P) + size(Q));
	for (int p : P)
		if (Q.find(p) != end(Q))
			ans -= 2;
	return min({ans, 1 + (int)size(Q), 1 + sz - (int)size(Q)});
}

int main()
{
	int n, m, s, p, q;
	cin >> n >> m >> s >> p >> q;
	s--;
	int k = (n + m - 1) / m;

	vector<unordered_set<int>> P(k), Q(k);
	for (int i = 0; i < p; i++)
	{
		int a;
		cin >> a;
		a--;
		P[a / m].insert(a);
	}
	for (int i = 0; i < q; i++)
	{
		int a;
		cin >> a;
		a--;
		Q[a / m].insert(a);
	}

	int ans = 0, l = s, r = s;
	for (int i = 0; i < k; i++)
	{
		int c = cost(P[i], Q[i], i == n / m ? n % m : m);
		if (c)
		{
			l = min(l, i);
			r = max(r, i);
			ans += c;
		}
	}
	cout << ans + r - l + min(r - s, s - l);
}
