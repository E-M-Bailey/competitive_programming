#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

int64_t constexpr MOD = 998244353;

int64_t t;

unordered_map<int64_t, unordered_map<int, int64_t>> DP;


int f(int64_t n, int k)
{
	cerr << ' ' << n << ' '  << k << endl;
	auto [it, ins] = DP[n].try_emplace(k, 0);
	auto &dp = it->second;
	if (!ins)
		return dp;

	if (n < 0)
		return dp = 0;
	if (k == 0)
		return dp = n <= t;
	if (n == 0)
		return dp = 1;

	dp = 0;
	int64_t lim = (((int64_t)1 << (k + 1)) - 1) * t;
	if (n > lim || n < 0)
		return dp;

	for (int i = 0; i <= t; i++)
		dp = (dp + f(n - (i << k), k - 1)) % MOD;
	return dp;
}


int main()
{
	int64_t n;
	cin >> n >> t;
	cout << f(n, 57);

	
}



/*
#define len(a) int((a).size())
using ll = long long;
using ld = long double;
constexpr const int iinf = 1e9 + 7;
constexpr const ll inf = 1e18;
constexpr const ll mod = 998244353;
#define printDecimal(d) \
	std::cout << std::setprecision(d) << std::fixed

int main()
{
	ll n;
	ll t;
	cin >> n >> t;

	map<pair<ll, ll>, ll> cache;
	function<ll(ll, ll)> rec = [&](ll val, ll rem)
		{
			auto it = cache.find(std::make_pair(val, rem));
			if (it != cache.end()) return it->second;
			if (val == 0 && rem == -1)
			{
				return cache[make_pair(val, rem)] = 1ll;
			}
			if (val < 0 || rem < 0) return 0ll;
			ll ret = 0;
			cerr << rem << ' ' << n
			ll lb = max(((n + t) >> rem) - t, 0ll), rb = min(n >> rem, t);
			assert(lb <= rb);
			for (ll i = lb; i <= rb; i++)
			{
				ll curr = val - (t << rem);
				ret = (ret + rec(curr, rem - 1)) % mod;
			}
			return cache[make_pair(val, rem)] = ret;
		};

	ll ans = 0;
	for (ll i = 0; i < 60; i++)
	{
		for (ll j = 1; j <= t; j++)
		{
			ll rem = n - (j << i);
			ans = (ans + rec(rem, i - 1)) % mod;
		}
	}
	cout << ans << '\n';

}*/