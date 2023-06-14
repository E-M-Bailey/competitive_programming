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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M)
{
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod)
{
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n)
{
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
		s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : A)
	{
		ull p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
		{
			p = modmul(p, p, n);
		}
		if (p != n - 1 && i != s) return 0;
	}
	return 1;
}

ull pollard(ull n)
{
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1)
	{
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n)
{
	if (n == 1) return {};
	if (isPrime(n)) return { n };
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

vector<pair<ull, int>> fac2(ull n)
{
	auto fac = factor(n);
	sort(all(fac));
	int m = sz(fac);
	vector<pair<ull, int>> ans;
	rep(i, 0, m)
	{
		if (ans.empty() || ans.back().first != fac[i])
			ans.emplace_back(fac[i], 1);
		else
			ans.back().second++;
	}
	return ans;
}

long long tot(long long N)
{
	long long res = 1;
	for (auto [p, fr] : fac2(N))
	{
		//if (N % p)
		//	cerr << "help" << endl;
		//if (N % p == 0)
		//{
			while (N % p == 0)
			{
				N /= p;
				res *= p;
			}
			res /= p;
			res *= p - 1;
		//}
	}
	if (N > 1) res *= N - 1;
	return res;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);


	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		long long N;
		cin >> N;
		long long res = 0;
		auto pf = fac2(N);
		//for(auto [p, f] : pf){
		//	cerr << p << " ";
		//}
		//cerr << endl;
		ll div = 1;
		int m = sz(pf);
		vector<int> M(m);
		const auto incr = [&]()
		{
			for (int i = 0; i < m; i++)
			{
				if (M[i] < pf[i].second)
				{
					M[i]++;
					div *= pf[i].first;
					return true;
				}
				else
				{
					while (div % pf[i].first == 0)
						div /= pf[i].first;
					M[i] = 0;
				}
			}
			return false;
		};
		do
		{
			//cerr << div << endl;
			auto f = div;
			//if (N % f != 0) continue;
			res += tot(N / f + 1);
			//if (f != N / f) res += tot(f + 1);
		} while (incr());
		cout << res << endl;
	}
	return 0;
}