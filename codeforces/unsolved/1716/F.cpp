#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int t = 1;
	cin >> t;
	while (t--)
		go();
}

typedef long long ll;

ll constexpr MOD = 998244353, PHI = MOD - 1;

ll constexpr mpow(ll a, ll b)
{
	if ((a %= MOD) < 0)
		a += MOD;
	if ((b %= PHI) < 0)
		b += PHI;

	ll ans = 1;
	for (; b; b /= 2, a = a * a % MOD)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

ll fac(int n)
{
	static vector<ll> F{1};
	while (n >= (int)size(F))
		F.push_back((F.back() * (ll)size(F)) % MOD);
	return F[n];
}

ll nCr(int n, int r)
{
	if (r < 0 || r > n)
		return 0;
	return fac(n) * mpow(fac(r) * fac(n - r), -1) % MOD;
}

void go()
{
	ll n, m, k;
	cin >> n >> m >> k;

	ll b = m / 2, a = (m + 1) / 2;
	if (b == 0)
	{
		cout << mpow(a, n) * mpow(n, k) % MOD << '\n';
		return;
	}
	
	ll c = a * mpow(b, -1) % MOD, cp1 = (c + 1) % MOD;
	// cerr << b << ' ' << a << ' ' << c << endl;

	// vector<ll> A(k + 1);
	// A[0] = mpow(1 - c, -1);
	// for (int i = 1; i <= k; i++)
	// 	A[i] = A[i - 1] * A[0] % MOD;

	// vector<ll> B(k + 1);
	// B[0] = MOD - mpow(c, n);
	// for (int i = 1; i <= k && i <= n; i++)
	// 	B[i] = B[i - 1] * ci % MOD * (n + 1 - i) % MOD * mpow(i, -1) % MOD;
	// B[0] = (1 + B[0]) % MOD;

	// vector<ll> C(k + 1);
	// for (int i = 0; i <= k; i++)
	// 	for (int j = 0; i + j <= k; j++)
	// 		C[i + j] = (C[i + j] + A[i] * B[j]) % MOD;

	vector<ll> C(k + 1);
	C[0] = mpow(cp1, n);
	for (int i = 1; i <= k && i <= n; i++)
		C[i] = C[i - 1] * (n + 1 - i) % MOD * mpow(cp1 * i, -1) % MOD;

	// for (auto c : C)
	// 	cerr << c << ' ';
	// cerr << endl;

	for (int i = 0; i < k; i++)
	{
		for (ll j = 0; i + j <= k; j++)
		{
			C[j] = C[j] * j % MOD;
			if (j > 0)
				C[j - 1] = (C[j - 1] + c * C[j]) % MOD;
		}
		// for (auto c : C)
		// 	cerr << c << ' ';
		// cerr << endl;
	}
	// cerr << endl;

	cout << C[0] * mpow(b, n) % MOD << '\n';
}
