#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mpow(ll a, ll b, ll m)
{
	if ((a %= m) < 0)
		a += m;
	if ((b %= m - 1) < 0)
		b += m - 1;
	ll ans = 1;
	for (; b; a = a * a % m, b /= 2)
		if (b % 2)
			ans = ans * a % m;
	return ans;
}

void solve(bitset<1 << 30> &S)
{
	ll m, n;
	cin >> m >> n;

	vector<ll> A(n);
	for (ll &a : A)
	{
		cin >> a;
		S[a] = true;
	}

	if (n == m)
	{
		cout << "0 1";
		return;
	}
	if (n + 1 == m)
	{
		int exc = 0;
		while (S[exc])
			exc++;
		cout << (exc == m - 1 ? 0 : exc + 1) << " 1";
		return;
	}
	if (m < 7)
	{
		sort(begin(A), end(A));
		do
		{
			bool good = true;
			ll	 d	  = n == 1 ? 0 : A[1] - A[0];
			if (d < 0)
				d += m;
			for (int i = 0; i < n - 1; i++)
				good &= (A[i] + d + m - A[i + 1]) % m == 0;
			if (good)
			{
				cout << A[0] << ' ' << d;
				return;
			}
		}
		while (next_permutation(begin(A), end(A)));
		cout << "-1";
		return;
	}

	ll s1 = 0, s2 = 0;
	for (ll a : A)
	{
		s2 = (s2 + a * s1) % m;
		s1 = (s1 + a) % m;
	}

	ll d = 6 * s1 * mpow(n * (n + 1), -1, m) - 12 * s2 * mpow(n * (n + 1) * (n - 1), -1, m);
	if ((d %= m) < 0)
		d += m;
	ll x = -1;
	cerr << d << ' ' << x << ' ' << s1 << ' ' << s2 << endl;
	cerr << n * (n + 1) * (n - 1) % m << ' ' << n * (n + 1) * (n - 1) * d % m << ' ' <<  (6 * (n - 1) * s1 - 12 * s2) % m << endl;
	for (ll a : A)
	{
		ll pr = a - d;
		if (pr < 0)
			pr += m;
		cerr << a << ' ' << pr << ' ' << S[pr] << endl;
		if (!S[pr])
		{
			x = a;
			break;
		}
	}
	for (int i = 1; i < n; i++)
		if (!S[(x + d * i) % m])
		{
			cout << "-1";
			return;
		}
	cout << x << ' ' << d;
}

int main()
{
	bitset<1 << 30> *S = new bitset<1 << 30>{};
	solve(*S);
	delete S;
}
