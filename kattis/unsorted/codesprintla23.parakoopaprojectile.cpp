#include <bits/stdc++.h>

using namespace std;

typedef long double T;

struct line
{
	T m, b;
};

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<line> L(n);
	T best = numeric_limits<T>::infinity();
	unordered_map<T, T> UM;
	for (auto &[m, b] : L)
	{
		T x, y;
		cin >> x >> y;
		if (UM.emplace(x, y).second)
		{
			// a x^2 + b x = y
			// a = (y - b x) / x^2
			m = -1 / x;
			b = y * m * m;
		}
		else
			best = min(best, x);
	}
	// minimize -b/a

	sort(begin(L), end(L), [&](line const &a, line const &b)
		{
			if (a.m != b.m)
				return a.m < b.m;
			else
				return a.b > 	 b.b;
		});
	vector<line> lower, upper;
	for (const line &l : L)
	{
		auto [m3, b3] = l;
		while (!lower.empty())
		{
			auto [m2, b2] = lower[lower.size() - 1];
			if (m2 == m3)
			{
				
			}
			auto [m1, b1] = lower[lower.size() - 2];
			if (m2 == l.m)
			{
				lower.pop_back();
			}
			T x1 =
		}
	}
}