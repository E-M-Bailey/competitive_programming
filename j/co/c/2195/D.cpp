#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

using ll = long long;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		vector<ll> F(n);
		for (ll &f : F)
			cin >> f;
		vector<ll> A(n);
		A[0] = F[0];
		A[n - 1] = F[n - 1];
		for (int i = 1; i < n - 1; ++i)
		{
			A[i] = (F[i - 1] - 2 * F[i] + F[i + 1]) / 2;
			A[0] -= i * A[i];
			A[n - 1] -= (n - 1 - i) * A[i];
		}
		A[0] /= n - 1;
		A[n - 1] /= n - 1;
		swap(A[0], A[n - 1]);
		for (ll a : A)
			cout << a << ' ';
		cout << '\n';
	}
}
