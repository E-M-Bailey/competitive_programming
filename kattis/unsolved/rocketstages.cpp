#include <bits/stdc++.h>

using namespace std;

typedef long double T;

const T g = 9.8;

int main()
{
	int n;
	cin >> n;

	vector<T> DP(10001);
	for (int i = 0; i < n; i++)
	{
		unsigned s, l, t, c;
		cin >> s >> l >> t >> c;
		if (max(s, l) > 10000)
			continue;

		for (int j = 10000; j >= s + l; j--)
		{
			int sj = j - l;
			if (t < g * j)
				continue;
			T dv = (t * log1p((T)l / sj) - g * l) / c;
			DP[j] = max(DP[j], DP[j - (s + l)] + dv);
		}
	}

	cout << round(*max_element(begin(DP), end(DP)));
}