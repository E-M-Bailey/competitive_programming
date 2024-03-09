#include <bits/stdc++.h>

using namespace std;

int main()
{
	long long n;
	cin >> n;
	vector<pair<int, long long>> P;
	for (long long i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			P.emplace_back(0, -i);
			do
				P.back().first++;
			while ((n /= i) % i == 0);
		}
	}
	if (n > 1)
		P.emplace_back(1, -n);

	cout << -max_element(begin(P), end(P))->second;
}
