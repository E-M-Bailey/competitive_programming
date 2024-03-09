#include <bits/stdc++.h>

using namespace std;

int qct = 0;

int qry(int a, int b, int c, int d)
{
	//if (c == n)
	//	return -qry(0, 0, a, b);
	//if (a > b || b > c || c > d || c >= n)
	//	exit(-1);
	cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
	int ans;
	cin >> ans;
	return -ans;
}

int main()
{
	int n;
	cin >> n;

	int lzlo = 0, lzhi = n;
	while (lzlo < lzhi)
	{
		int mid = (lzlo + lzhi + 1) / 2;
		int q = qry(0, 0, 0, mid);
		if (q < 0)
			lzhi = mid - 1;
		else
			lzlo = mid;
	}
	int lz = lzlo;
	if (lz == n)
	{
		cout << "! 0";
		return 0;
	}

	int r = n;
	vector<int> A;
	while (lz < r)
	{
		int lo = lz, hi = r, cur = 1;
		while (lo < hi)
		{
			int mid = (lo + hi + 1) / 2;
			int q = qry(lz, mid, mid, r);
			if (q == 0) cur = 0;
			if (q > 0)
				hi = mid - 1;
			else
				lo = mid;
		}
		A.push_back(cur);
		r = lo;
	}
	int ans = 0;
	while (!A.empty())
	{
		ans = 2 * ans + A.back();
		A.pop_back();
	}
	cout << "! " << ans << endl;
}