#include <bits/stdc++.h>

using namespace std;

int n;

auto const inf = numeric_limits<long double>::infinity();

vector<tuple<long double, long double, long double>> upper(vector<pair<long double, long double>> &L)
{
	sort(begin(L), end(L));
	vector<tuple<long double, long double, long double>> ans;
	for (auto [m, b] : L)
	{
		while (!ans.empty() && get<1>(ans.back()) == m)
			ans.pop_back();
		if (ans.empty())
		{
			ans.emplace_back(-inf, m, b);
			continue;
		}

		long double is;
		while ((is = (get<2>(ans.back()) - b) / (m - get<1>(ans.back()))) <= get<0>(ans.back()))
			ans.pop_back();
		ans.emplace_back(is, m, b);
	}
	return ans;
}

long double eval(vector<tuple<long double, long double, long double>> const &U, long double x)
{
	auto it = prev(partition_point(begin(U),
								   end(U),
								   [x](tuple<long double, long double, long double> seg)
								   {
									   return get<0>(seg) <= x;
								   }));
	return get<1>(*it) * x + get<2>(*it);
}

int main()
{
	cin >> n;
	vector<pair<long double, long double>> L(n);
	long double t0 = 0;
	for (int i = 0; i < n; i++)
	{
		long double t, v;
		cin >> t >> v;
		t0 = max(t0, t);
		L[i] = {v, -v * t};
	}

	auto top = upper(L);
	for (auto &[m, b] : L)
	{
		m *= -1;
		b *= -1;
	}
	auto bot = upper(L);

	vector<long double> X{t0};
	for (auto [x, m, b] : top)
		if (x >= t0)
			X.push_back(x);
	for (auto [x, m, b] : bot)
		if (x >= t0)
			X.push_back(x);

	long double ans = inf;
	for (long double x : X)
		ans = min(ans, eval(top, x) + eval(bot, x));

	cout << fixed << setprecision(13) << ans;
}
