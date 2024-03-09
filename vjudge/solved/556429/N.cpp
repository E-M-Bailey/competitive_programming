#include <bits/stdc++.h>

using namespace std;

/*
int besthub(int R, int L, int X[], long long B);

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		std::ignore = freopen(argv[1], "r", stdin);
		std::ignore = freopen(argv[2], "w", stdout);
	}

	int R, L;
	long long B;
	std::cin >> R >> L >> B;
	int X[100000];
	for (int i = 0; i < R; i++)
		std::cin >> X[i];
	std::cout << besthub(R, L, X, B);
}
*/

int besthub(int R, int, int X[], long long B)
{
	long long ls = 0, rs = 0;
	int best = 0;
	int l = 0, m = 0, r = 0;
	const auto bal = [&]()
	{
		if (r - m > m - l + 1)
		{
			rs -= X[m];
			ls += X[m++];
		}
	};
	while (rs += X[r], ++r <= R)
	{
		while (bal(), (long long)X[m] * (2 * m - r - l) + rs - ls > B)
			ls -= X[l++];
		best = max(best, r - l);
	}
	return best;
}