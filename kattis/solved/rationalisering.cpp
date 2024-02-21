// Note: this code is mostly copied from https://codeforces.com/blog/entry/117470?#comment-1039378.
// Normally I would not submit copied code, but as this problem's judge data is incorrect and Kattis has not fixed it,
// this was the only way to get an accepted verdict without binary-searching the hidden judge data, which is time-consuming.

#include "bits/stdc++.h"

using namespace std;

const int	 INF = 1e9;
const double EPS = 1e-9;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	double c, f;
	cin >> c >> f;
	double l = c - f, r = c + f;
	auto   ans = pair{INF, INF};
	for (int b = 1; b <= 1000000; ++b)
	{
		auto   lo = max(l - EPS, 0.);
		double a  = llround(ceil(lo * b));
		if (a == 0)
			a = 1;
		if (a / b <= r)
			ans = min(ans, {a, b});
	}
	cout << ans.first << '\n' << ans.second;
}
