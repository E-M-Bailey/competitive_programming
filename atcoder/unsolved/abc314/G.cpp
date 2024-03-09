#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, h;
	cin >> n >> m >> h;

	int64_t sum = 0;

	vector<int64_t> TS(m, 0);
	const auto cmp = [&](int i, int j)
		{
			return TS[i] < TS[j];
		};

	set<int, decltype(cmp)> S(cmp);
	int64_t s = 0;

	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		b--;

		auto it = S.find(b);
		if (it != S.end())
		{
			S.erase(it);
			s += TS[b];
		}

		s += a;
		TS[b] += a;

		while (s >= h)
		{
			
		}
	}
}