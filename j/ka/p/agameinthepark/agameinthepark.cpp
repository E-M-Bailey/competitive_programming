#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;

static array<int, 16> adv(array<int, 16> const &dp1, array<int, 4> const &XX)
{
	array<int, 16> dp2{};
	for (int m2 : { 0, 1, 2, 4, 5, 8, 9, 10 })
	{
		int sum = 0;
		for (int i = 0; i < 4; ++i)
			sum += ((m2 >> i) & 1) * XX[i];
		for (int m1 : { 0, 1, 2, 4, 5, 8, 9, 10 })
			if ((m1 & m2) == 0)
				dp2[m2] = max(dp2[m2], dp1[m1] + sum);
	}
	return dp2;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<array<int, 4>> X(n);
	for (int i = 0; i < 4; ++i)
		for (auto &XX : X)
			cin >> XX[i];
	array<int, 16> dp{};
	for (auto const &XX : X)
		dp = adv(dp, XX);
	cout << rng::max(dp);
}
