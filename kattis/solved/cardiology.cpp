#include <bits/stdc++.h>

using namespace std;

long long getS(long long a, long long pr, long long c, long long ba, vector<long long> &D)
{
	if (a == ba)
		return 0;
	long long i = a / c;
	if (D[i] >= 0)
		return D[i];
	return D[i] = 1 + getS(i + pr, pr, c, ba, D);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	long long r, c;
	cin >> r >> c;

	long long i0 = (r - 1) / 2, i1 = r / 2, j0 = (c - 1) / 2, j1 = c / 2;

	long long bestP = 0, bestI = 0, bestJ = 0, bestD = i0 + j0;
	for (long long p = 1; p < c; p++)
	{
		long long i = p * r / (c - 1);
		if (p * r % (c - 1) == 0)
		{
			if (i == r)
				i = r - 1;
			else
				continue;
		}
		if (i >= r)
			break;
		long long a = i + p * r;
		long long j = a % c;
		long long d = (i <= i0 ? i0 - i : i - i1) + (j <= j0 ? j0 - j : j - j1);
		if (d < bestD)
		{
			bestP = p;
			bestI = i;
			bestJ = j;
			bestD = d;
		}
	}

	long long		  s = 0;
	vector<long long> D(r, -1);
	for (int i = 0; i < r; i++)
		s = max(s, getS(i * c + (bestJ + 1) % c, bestP * r, c, bestI + bestP * r, D));
	cout << bestP + 1 << ' ' << bestI + 1 << ' ' << bestJ + 1 << ' ' << s << '\n';
}
