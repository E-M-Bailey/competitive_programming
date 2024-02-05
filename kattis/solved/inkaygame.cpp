#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int			n, l;
	long double p;
	cin >> n >> l >> p;

	vector<long double> POW(n + 1);
	POW[0] = 1;
	for (int i = 1; i <= n; i++)
		POW[i] = POW[i - 1] * p;

	vector<long double> P(n + 1), P2(n + 1);
	P[n] = 1;
	for (int i = 0; i < l; i++)
	{
		fill(begin(P2), end(P2), 0.l);
		for (int j = n; j > 0; j--)
		{
			long double q = (j > 1) * POW[j];
			P[j - 1] += q * P[j];
			long double s = (1 - q) * P[j] / 2;
			P2[j] += s;
			P2[j - 1] += s;
		}
		swap(P, P2);
	}
	P[0] = 0;
	cout << fixed << setprecision(6) << accumulate(begin(P), end(P), 0.l);
}
