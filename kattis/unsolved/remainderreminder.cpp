#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct bezout { ll x, y, g; };
bezout euclid(ll a, ll b)
{
	if (!b) return { 1, 0, a };
	auto [y, x, g] = euclid(b, a % b);
	return { x, y - a / b * x, g };
}

pair<ll, ll> crt(ll a, ll m, ll b, ll n)
{
	if (n > m) swap(a, b), swap(m, n);
	auto [x, y, g] = euclid(m, n);
	x = (b - a) % n * x % n / g * m + a;
	ll l = m * n / g;
	return { x < 0 ? x + l : x, l };
}

int main()
{
	ll R[3];
	int a, b;
	ll &c = R[0], &d = R[1], &e = R[2], f, g;
	cin >> a >> b >> c >> d >> e >> f >> g;
	vector<int> V;
	for (int dep = 1; dep * 2 < a; dep++)
	{
		V.push_back(dep * (a - 2 * dep) * (b - 2 * dep));
		// cerr << dep << ' ' << V.back() << endl;
	}
	sort(begin(V), end(V), greater<int>());
	// cerr << V[0] << endl;
	ll val = 0, mod = 1;
	for (int i = 0; i < 3; i++)
	{
		// cerr << R[i] << ' ' << V[i] << endl;
		tie(val, mod) = crt(val, mod, R[i], V[i]);
	}
	ll ans = f / mod * mod + val % mod;
	if (ans < f)
		ans += mod;
	// cerr << val << ' ' << mod << endl;
	cout << ans;
}