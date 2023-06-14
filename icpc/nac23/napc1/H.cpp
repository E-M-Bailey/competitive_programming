#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) int(size(x))
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const ll MOD = 1e9 + 7;

ll mpow(ll a, ll b)
{
	ll ans = 1;
	for (; b; a = a * a % MOD, b /= 2)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int tc;
	cin >> tc;
	while (tc--)
	{
		ll R, C;
		cin >> R >> C;
		ll ans = 1;
		cout << mpow(3, R + C) * mpow(2, R * C) % MOD << '\n';
	}
}