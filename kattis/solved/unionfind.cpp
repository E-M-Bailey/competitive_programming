#include <bits/stdc++.h>
using namespace std;
struct dso
{
	int			n;
	vector<int> P, R;
	dso(int n) : n(n), P(n), R(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		R[x] += R[x] == R[y];
		P[y] = x;
		return true;
	}
};
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	dso D(n);
	while (q--)
	{
		char c;
		int	 a, b;
		cin >> c >> a >> b;
		if (c == '=')
			D.onion(a, b);
		else
			cout << (D.find(a) == D.find(b) ? "yes\n" : "no\n");
	}
}
