#include <bits/stdc++.h>

using namespace std;

template<long long P = 1000000000000000ll, long long K = 15>
long long solve(long long x)
{
	if (x < P)
		return solve<P / 10, K - 1>(x);
	if (x == P)
		return K * 45 * (P / 10);

	long long q = x / P, m = x % P;
	return solve<P, K>(P) * q + solve<1, 0>(q) * P + solve<P / 10, K - 1>(m) + m * q;
}
template<>
long long solve<1, 0>(long long x)
{
	return x * (x - 1) / 2;
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		long long a, b;
		cin >> a >> b;
		cout << solve(b + 1) - solve(a) << '\n';
	}
}
