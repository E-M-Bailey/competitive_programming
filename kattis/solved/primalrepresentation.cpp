#include <bits/stdc++.h>

using namespace std;

int main()
{
	constexpr int MAXP = 46341;
	vector<int>	  P;
	P.reserve(MAXP);
	vector<bool> C(MAXP + 1);
	for (int i = 2; i <= MAXP; i++)
	{
		if (C[i])
			continue;
		P.push_back(i);
		for (int j = i * 2; j <= MAXP; j += i)
			C[j] = true;
	}

	int					   n;
	vector<pair<int, int>> F;
	while (cin >> n)
	{
		F.clear();
		if (n < 0)
		{
			F.emplace_back(-1, 1);
			n = -n;
		}
		for (int p : P)
		{
			if (p * p > n)
				break;
			if (n % p == 0)
			{
				F.emplace_back(p, 1);
				while ((n /= p) % p == 0)
					F.back().second++;
			}
		}
		if (n > 1)
			F.emplace_back(n, 1);
		for (auto [p, c] : F)
		{
			cout << p;
			if (c > 1)
				cout << '^' << c;
			cout << ' ';
		}
		cout << '\n';
	}
}
