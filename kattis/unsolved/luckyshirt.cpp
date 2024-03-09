#include <bits/stdc++.h>

using namespace std;

typedef double T;

T bpow(T st, T a, int b)
{
	T ans = st;
	for (; b; a *= a, b /= 2)
		if (b % 2)
			ans *= a;
	return ans;
}

int main()
{
	int n, i, k;
	/*
	while (cin >> n >> i >> k)
	{
		i--;
		vector<T> P(n);
		P[n - 1] = 1 / T(n);
		for (int j = i; j < n - 1; j++)
			P[j] = -1 / T(j + 2);

	}*/

	cin >> n >> i >> k;
	i--;
	vector<T> P(n);
	// S^-1 P
	if (i > 0)
		P[i - 1] = -T(i) / (i + 1);
	for (int j = i; j < n - 1; j++)
		P[j] = T(1) / (j + 2);
	P[n - 1] = T(1) / n;

	// for (T p : P)
	// 	cerr << ' ' << p << endl;

	// J S^-1 P
	for (int j = 0; j < n; j++)
		P[j] = bpow(P[j], T(j + 1) / n, k);

	// S J S^-1
	vector<T> S(n);
	S[n - 1] = P[n - 1];
	for (int j = n - 2; j >= 0; j--)
	{
		S[j] = S[j + 1] + P[j] / (j + 1);
	}

	T ans = 0;
	for (int j = 0; j < n; j++)
	{
		ans += S[j] * (j + 1);
		if (j > 0)
			ans -= P[j - 1] * (j + 1);
	}

	cout << fixed << setprecision(7) << ans;
}