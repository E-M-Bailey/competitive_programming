#include <bits/stdc++.h>

using namespace std;

int main()
{
	int c;
	cin >> c;
	c--;
	vector<bool> C;
	while (c)
	{
		C.push_back(c % 2);
		c /= 2;
	}
	reverse(begin(C), end(C));

	int k = (int)C.size();
	vector<pair<long double, long double>> DP(k + 1);
	DP.back() = make_pair(0, 0);
	for (int i = k - 1; i >= 0; i--)
	{
		DP[i] = DP[i + 1];
		if (C[i])
		{
			DP[i].first += k - 1 - i;
		}
		else
		{
			DP[i].second += 1;
		}
		DP[i].first /= 2;
		DP[i].second /= 2;
		DP[i].first += 1;
	}

	cout << fixed << setprecision(6) << DP[0].first / (1 - DP[0].second);
}