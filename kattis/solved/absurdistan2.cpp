#include <bits/stdc++.h>

using namespace std;

vector<long double>			T(141, -1);
vector<vector<long double>> F(141, vector<long double>(141, -1));

long double forest(int m, int n);

long double tree(int n)
{
	long double &t = T[n];
	if (t < 0)
	{
		t = 0;
		for (int m = 0; m < n; m++)
			t += forest(m, n - 1);
		t *= n;
	}
	return t;
}

long double forest(int m, int n)
{
	long double &f = F[m][n];
	if (f < 0)
	{
		if (m == 0)
			f = n == 0;
		else
		{
			f				= 0;
			long double num = 1, den = 1;
			for (int k = 1; k <= n; k++)
			{
				f += tree(k) * forest(m - 1, n - k) * num / den;
				num *= n - k;
				den *= k;
			}
		}
	}
	return f;
}

long double wc_simp_func(int n)
{
	long double c	= 0;
	long double fac = 1;
	for (int m = 2; m <= n; m++)
	{
		c += forest(m, n) * fac;
		fac *= m;
	}
	return c;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	cout << fixed << setprecision(9) << wc_simp_func(n) * powl(n - 1, -n);
}
