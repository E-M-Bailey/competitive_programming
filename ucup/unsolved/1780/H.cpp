#include <bits/stdc++.h>

using namespace std;

long double const P = (1 + sqrtl(5)) / 2;

int qry(int lo, int hi)
{
	if (lo == hi)
		return lo;
	cout << "? " << lo << ' ' << hi << '\n' << flush;
	int ans;
	cin >> ans;
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;

		int lo = 1, hi = n, snd = qry(1, n);
		while (lo < hi)
		{
			if (lo + 1 == hi)
			{
				if (snd == lo)
					lo = hi;
				else
					hi = lo;
				break;
			}
			int sz = hi - lo + 1;
			sz = (int)round(sz / P);
			if (snd - lo <= hi - snd)
			{
				int q = qry(lo, lo + sz - 1);
				if (q == snd)
				{
					hi = lo + sz - 1;
				}
				else
				{
					lo = lo + sz;
					snd = qry(lo, hi);
				}
			}
			else
			{
				int q = qry(hi - sz + 1, hi);
				if (q == snd)
				{
					lo = hi - sz + 1;
				}
				else
				{
					hi = hi - sz;
					snd = qry(lo, hi);
				}
			}
		}
		cout << "! " << lo << '\n' << flush;
	}
}


