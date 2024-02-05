#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("O3")

struct pp
{
	int p, pp;
};

int constexpr LIM = 5e7 + 1;
pp HPP[LIM]{};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	for (int i = 2; i < LIM; i++)
	{
		if (HPP[i].p > 0)
			continue;
		for (int j = 1, k = i; k < LIM; j++, k += i)
		{
			HPP[k] = {i, i};
			if (HPP[j].p == i)
				HPP[k].pp *= HPP[j].pp;
		}
	}

	int N;
	while (cin >> N)
	{
		__int128_t sum = 0;
		for (int i = 2; i <= N; i++)
		{
			int d	= N / i;
			int tot = i;
			for (int j = i; j > 1; j /= HPP[j].pp)
			{
				tot = tot / HPP[j].p * (HPP[j].p - 1);
			}
			sum += (__int128_t)d * (d + 1) / 2 * tot;
		}
		string ans;
		do
			ans.push_back(char(sum % 10 + '0'));
		while (sum /= 10);
		reverse(begin(ans), end(ans));
		cout << ans << '\n';
	}
}
