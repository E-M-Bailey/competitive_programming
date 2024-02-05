#include <bits/stdc++.h>

using namespace std;

struct point
{
	int		   x;
	int		   y;
	int		   i;
	friend int operator^(const point &a, const point &b)
	{
		return a.x * b.y - a.y * b.x;
	}
	int norm2() const
	{
		return x * x + y * y;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<point> P(n);
		int			  idx = 0;
		for (int i = 0; i < n; i++)
		{
			auto &[x, y, j] = P[i];
			j				= i;
			cin >> x >> y;
			if (y < P[idx].y || y == P[idx].y && x < P[idx].x)
				idx = i;
		}

		swap(P[idx], P[0]);
		point off = P[0];
		for (auto &[x, y, i] : P)
		{
			x -= off.x;
			y -= off.y;
		}

		sort(1 + begin(P),
			 end(P),
			 [](const point &a, const point &b)
			 {
				 int c = a ^ b;
				 return c ? c > 0 : a.norm2() < b.norm2();
			 });

		auto it = prev(P.end());
		while ((*it ^ P.back()) == 0)
			--it;
		reverse(next(it), P.end());

		for (const auto &[x, y, i] : P)
			cout << i << ' ';
		cout << '\n';
	}
}