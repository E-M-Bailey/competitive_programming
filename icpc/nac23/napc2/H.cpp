#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef __int128_t big;

const ll P1 = 1e9 + 7, P2 = 1e9 + 9, P3 = 43;
//typedef pair<ll, ll> pll;
struct pll
{
	ll first, second, third;
};

pll operator*(pll const &a, pll const &b)
{
	return { a.first * b.first % P1, a.second * b.second % P2, a.third * b.third % P3 };
}

ll mpow(ll a, ll b, ll m)
{
	ll ans = 1;
	for (; b; a = a * a % m, b /= 2)
		if (b & 1)
			ans = ans * a % m;
	return ans;
}

pll inv(pll a)
{
	return { mpow(a.first, P1 - 2, P1), mpow(a.second, P2 - 2, P2), mpow(a.third, P3 - 2, P3) };

}
bool operator==(pll const &l, pll const &r)
{
	return tie(l.first, l.second, l.third) == tie(r.first, r.second, r.third);
}
bool operator<(pll const &l, pll const &r)
{
	return tie(l.first, l.second, l.third) < tie(r.first, r.second, r.third);
}

big euclid(big a, big b, big &x, big &y)
{
	if (!b) return x = 1, y = 0, a;
	big d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;
}

big crt(big a, big m, big b, big n)
{
	if (n > m) swap(a, b), swap(n, m);
	big x, y, g = euclid(m, n, x, y);
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m * n / g : x;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int d, h;
	cin >> d >> h;
	h--;

	vector<pll> F(h + 1);
	F[0].first = F[0].second = F[0].third = 1;
	rep(i, 1, h + 1)
		F[i] = F[i - 1] * pll{ i, i, i };

	vector<vector<vector<pll>>> DP(d + 1, vector<vector<pll>>(h + 1));
	DP[d][0].emplace_back(F[h]);

	for (int i = d - 1; i >= 0; i--)
	{
		rep(h2, 0, h + 1)
		{
			auto &dp = DP[i][h2];
			rep(n, 0, h2 + 1)
				for (auto rec : DP[i + 1][h2 - n])
					dp.push_back(rec * inv(F[n]));
			sort(all(dp));
			dp.erase(unique(all(dp)), end(dp));
			//cerr << i << ' ' << h2 << endl;
			//for (auto [a, b, c] : dp)
			//	cerr << ' ' << a;
			//cerr << endl;
		}
	}

	vector<ll> ans;
	for (auto [a, b, c] : DP[0][h])
		ans.push_back((ll)crt(crt(a, P1, b, P2), (big)P1 * P2, c, P3));
	sort(all(ans));
	ans.erase(unique(all(ans)), end(ans));
	for (auto a : ans)
		cout << a << '\n';

}

// g+ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out