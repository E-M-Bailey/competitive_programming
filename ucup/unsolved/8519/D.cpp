#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr ll M = 1000000007;

int main()
{
	int n;
	cin >> n;
	vector<ll> A(n);
	for (auto &a : A)
		cin >> a;

	vector<ll> S0(61, 1), S1(61);
	ll cur = 0;
	for (ll a : A)
	{
		cur = 0;
		ll p2 = 1;
		for (int i = 0; i < 61; i++, p2 = p2 * 2 % M)
		{
			if (a & (1ll << i))
				swap(S0[i], S1[i]);
			// cerr << S0[i] << '_' << S1[i] << ' ';
			cur = (cur + S1[i] * p2) % M;
		}
		for (int i = 0; i < 61; i++)
			S0[i] = (S0[i] + cur) % M;
	}
	cout << cur << '\n';
}
