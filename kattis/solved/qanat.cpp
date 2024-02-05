#include <bits/stdc++.h>

using namespace std;

int w, h, n;

typedef long double T;

const T E = 1e-9l;

void tridiag(vector<T> d, const vector<T> &p, const vector<T> &q, vector<T> &b)
{
	vector<int> tr(n);
	for (int i = 0; i < n - 1; i++)
	{
		if (abs(d[i]) < E * abs(p[i]))
		{
			b[i + 1] -= b[i] * d[i + 1] / p[i];
			if (i + 2 < n)
				b[i + 2] -= b[i] * q[i + 1] / p[i];
			d[i + 1] = q[i];
			tr[++i]	 = 1;
		}
		else
		{
			d[i + 1] -= p[i] * q[i] / d[i];
			b[i + 1] -= b[i] * q[i] / d[i];
		}
	}
	for (int i = n; i--;)
	{
		if (tr[i])
		{
			swap(b[i], b[i - 1]);
			d[i - 1] = d[i];
			b[i] /= p[i - 1];
		}
		else
		{
			b[i] /= d[i];
			if (i)
				b[i - 1] -= b[i] * p[i - 1];
		}
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> w >> h >> n;
	n += 2;

	T s = (T)h / w;
	T g = (s * s - 1) / 2;

	vector<T> b(n, 0), d(n, 1), p(n - 1, g), q(n - 1, g);
	p[0] = q[n - 2] = 0;
	b[n - 1]		= w;

	tridiag(d, p, q, b);

	T c = 0;
	for (int i = 1; i < n; i++)
	{
		T cur = (s - 1) * b[i - 1] + (s + 1) * b[i];
		c += cur * cur / 4;
		if (i < n - 1)
			c -= s * s * b[i] * b[i] / 2;
	}

	cout << fixed << setprecision(5) << c << '\n';
	for (int i = 0; i < min(n - 2, 10); i++)
		cout << b[i + 1] << '\n';
}
