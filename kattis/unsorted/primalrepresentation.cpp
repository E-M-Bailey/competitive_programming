#include <bits/stdc++.h>

using namespace std;

constexpr int LIM = 50000;
bitset<LIM> C{};
vector<int> P;

int main()
{
	for (int i = 2; i < LIM; i++)
	{
		if (C[i]) continue;
		P.push_back(i);
		for (int j = i * 2; j < LIM; j += i)
			C[j] = true;
	}

	int n;
	while (cin >> n)
	{
		if (n < 0)
		{
			cout << "-1 ";
			n *= -1;
		}
		for (int p : P)
		{
			int ct = 0;
			while (n % p == 0)
			{
				ct++;
				n /= p;
			}
			if (ct)
			{
				cout << p;
				if (ct > 1)
					cout << '^' << ct;
				cout << ' ';
			}
		}
		if (n > 1)
		{
			cout << n;
		}
		cout << '\n';
	}
}