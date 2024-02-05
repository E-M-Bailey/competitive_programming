#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

array<array<short, 1024>, 1001> pre()
{
	array<array<int, 1024>, 1001> p{};
	p[0][0] = 0xffff;
	for (int i = 1; i <= 1000; ++i)
		for (int j = 0; j < 1024; ++j)
		{
			int k  = j ^ i;
			int pj = p[i - 1][j];
			int pk = p[i - 1][k];

			if (pk && (!pj || (pk & 0xffff0000) >= (pj & 0xffff0000)))
				p[i][j] = (pk & 0xffff0000) + 0x10000 + i;
			else
				p[i][j] = pj;
		}
	array<array<short, 1024>, 1001> ans{};
	for (int i = 0; i <= 1000; ++i)
		for (int j = 0; j < 1024; ++j)
			ans[i][j] = short(p[i][j] & 0xffff);
	return ans;
}
array<array<short, 1024>, 1001> P = pre();

int t, m, x, A[1000], *a = A;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> t;
	while (t--)
	{
		cin >> m;
		x = m;
		do
		{
			m = *a++ = P[m][x];
			x ^= m;
			m--;
		}
		while (P[m][x] != -1);
		cout << (a - A) << '\n';
		do
			cout << *--a << ' ';
		while (a != A);
		cout << '\n';
	}
}
