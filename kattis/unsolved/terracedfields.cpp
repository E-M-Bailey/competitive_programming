#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

/*
#define len(a) int((a).size())
using ll = long long;
constexpr const int iinf = 1e9 + 7;

#define printDecimal(d) \
	cout << setprecision(d) << fixed


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t--)
	{
		ll n; std::cin >> n;
		auto d = n / 200;
		auto cost = [](ll v) -> ll
			{
				ll ans = 0;
				while (v)
				{
					ans += (v % 10 == 8 || v % 10 == 6);
					v /= 10;
				}
				return ans;
			};
		ll ret = d * 16 + cost(n);
		for (auto x = d * 200; x <= n; x += 8)
		{
			ret += cost(x);
			if (x == n) ret -= cost(n);
		}
		std::cout << ret << '\n';
	}

}

*/

typedef long long ll;

int cost(ll i)
{
	int ans = 0;
	while (i)
	{
		ans += i % 10 == 6 || i % 10 == 8;
		i /= 10;
	}
	return ans;
}

template<bool by8>
ll solve(ll n)
{
	if (n < 1000)
	{
		ll ans = 0;
		for (ll i = 0; i < n; i += (by8 ? 8 : 1))
			ans += cost(i);
		cerr << (by8 ? "" : " ") << n ? 
		return ans;
	}
	else if (n % 1000)
	{
		ll rd = n / 1000 * 1000;
		ll c = cost(rd);
		return solve<by8>(rd) + solve<by8>(n - rd) + (by8 ? n - rd : (n - rd) / 8) * c;
	}
	else
	{
		n /= 1000;
		return (by8 ? 106 : 600) * n + solve<0>(n) * (by8 ? 125 : 1000);
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		ll n;
		cin >> n;
		cout << solve<1>(n) + cost(n) << '\n';
	}
}