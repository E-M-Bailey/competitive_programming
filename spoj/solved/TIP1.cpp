#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 1e7;

vi P; // primes
bool C[MAXN]; // composite?
int F[MAXN], K[MAXN]; // function value, power of min pf

void sieve(int n)
{
	fill_n(C, n, 0); F[1] = 1; P.clear();
	rep(i, 2, n)
	{
		if (!C[i])
		{
			P.push_back(i);
			K[i] = 1;
			F[i] = i - 1; // f(i) for i prime (custom)
		}
		for (int j = 0, x; j < sz(P) && (x = i * P[j]) < n; ++j)
		{
			C[x] = K[x] = 1;
			if (i % P[j]) F[x] = F[i] * F[P[j]]; // f(i*p), p doesn't divide i
			else
			{
				F[x] = F[i] * P[j]; // f(ip), p = i's min pf (custom)
				K[x] += K[i];
				break;
			}
		}
	}
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit); // Not for weird formats

	sieve(MAXN);

	double record = 1000;
	vector<int> vals;
	int dig[10]{};
	rep(i, 2, MAXN)
	{
		double cur = i / (double)F[i];
		if (cur > record)
			continue;
		for (int x = i; x; x /= 10)
			dig[x % 10]++;
		for (int x = F[i]; x; x /= 10)
			dig[x % 10]--;
		bool good = true;
		rep(j, 0, 10)
		{
			good &= dig[j] == 0;
			dig[j] = 0;
		}
		if (good)
		{
			record = cur + 1e-9;
			vals.push_back(i);
		}
	}
	int T;
	cin >> T;
	while (T--)
	{
		int M;
		cin >> M;
		auto it = lower_bound(all(vals), M);
		if (it == begin(vals))
			cout << "No solution.\n";
		else
			cout << *prev(it) << '\n';
	}
}