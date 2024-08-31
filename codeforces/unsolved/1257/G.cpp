#include <bits/stdc++.h>

using namespace std;

typedef long long	ll;
typedef vector<int> vi;
#define sz(C)		 (int(size(C)))
#define rep(i, l, r) for (int i = l; i < r; i++)

const ll mod = (119 << 23) + 1, root = 62; // = 998244353

// Source: KACTL
ll modpow(ll b, ll e)
{
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1)
			ans = ans * b % mod;
	return ans;
}

// Source: KACTL
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void			   ntt(vl &a)
{
	int		  n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++)
	{
		rt.resize(n);
		ll z[]				   = {1, modpow(root, mod >> s)};
		rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k)
			rep(j, 0, k)
			{
				ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
				a[i + j + k] = ai - z + (z > ai ? mod : 0);
				ai += (ai + z >= mod ? z - mod : z);
			}
}
vl conv(const vl &a, const vl &b)
{
	if (a.empty() || b.empty())
		return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = (int)modpow(n, mod - 2);
	vl	L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i, 0, n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	map<int, int> F;
	for (int i = 0; i < n; i++)
	{
		int p;
		cin >> p;
		F[p]++;
	}

	auto const cmp = [](vl const &a, vl const &b)
	{
		return size(a) > size(b);
	};

	priority_queue<vl, vector<vl>, decltype(cmp)> PQ(cmp);

	for (auto [p, f] : F)
		PQ.emplace(f + 1, 1ll);

	while (size(PQ) > 1)
	{
		vl a = PQ.top();
		PQ.pop();
		vl b = PQ.top();
		PQ.pop();
		PQ.push(conv(a, b));
	}

	vl X = PQ.top();

	ll ans = 1;
	for (int i = 1; i * 2 <= n; i++)
		ans += X[i] - X[i - 1];

	if ((ans %= mod) < 0)
		ans += mod;

	cout << ans;
}
