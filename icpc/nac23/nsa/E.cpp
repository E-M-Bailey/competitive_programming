#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef long double T;
const T E = 1e-9l;

vector<char> varname;
vector<int> varid(256, -1);

struct rel
{
	valarray<T> a;
	T b;
	rel(int n) : a(n) {}
};

ostream &operator<<(ostream &os, rel const &R)
{
	for (auto aa : R.a)
		os << aa << ' ';
	os << ">= " << R.b;
	return os;
}

// sum_i a_i x_i >= 0

bool eq(valarray<T> &a, valarray<T> &b)
{
	T ans = 0;
	rep(i, 0, sz(a))
		ans = max(ans, abs(b[i] - a[i]));
	return ans < E;
}

bool solve(int n, int m, vector<rel> &rels, vector<T> &I)
{
	if (n == 0)
		return true;

	vi l, o, r;
	rep(i, 0, m)
	{
		auto a = rels[i].a[n - 1];
		(a < -E ? r : a > E ? l : o).push_back(i);
	}

	cerr << "input " << n << ' ' << sz(rels) << endl;
	for (auto rr : rels)
		cerr << ' ' << rr << endl;

	vector<rel> rels2;
	for (int i : o)
		rels2.push_back(rels[i]);
	for (int i : l)
		for (int j : r)
		{
			auto L = rels[i], R = rels[j];
			auto la = L.a[n - 1], ra = R.a[n - 1];
			L.a /= la;
			L.b /= la;
			R.a /= ra;
			R.b /= ra;
			bool e = eq(L.a, R.a);
			if (e && R.b < L.b - E)
				return false;
			else if (e)
				continue;
			L.a -= R.a;
			L.b -= R.b;

			rels2.push_back(move(L));
		}
	cerr << "help " << sz(rels2) << endl;

	decltype(rels2) rels3;
	vector<bool> add(sz(rels2), true);

	if (n > 1)
	{
		rep(i, 0, sz(rels2))

		{
			rep(j, i + 1, sz(rels2))
			{

				if (eq(rels2[i].a, rels2[j].a))
				{
					auto L = rels2[i], R = rels2[j];
					auto la = L.a[n - 2], ra = R.a[n - 2];
					if (abs(la) < E || abs(ra) < E)
						continue;
					bool nl = la < 0, nr = ra < 0;
					L.a /= la;
					L.b /= la;
					R.a /= ra;
					R.b /= ra;
					bool e = eq(L.a, R.a);
					cerr << ' ' << L << ' ' << R << ' ' << e << endl;
					if (!e)
						continue;
					if (!nl && !nr)
						add[L.b > R.b ? i : j] = false;
					else if (nl && nr)
						add[L.b < R.b ? i : j] = false;
					else if (nl && !nr)
					{
						if (R.b < L.b + E) return false;
					}
					else
						if (R.b > L.b - E) return false;
				}
			}
		}
	}

	rep(i, 0, sz(rels2))
		if (add[i])
			rels3.push_back(rels2[i]);

	cerr << endl << sz(rels3) << endl;
	rep(i, 0, sz(rels3))
	{
		rep(j, 0, sz(rels3))
		{
			cerr << eq(rels3[i].a, rels3[j].a) << ' ';
		}
		cerr << endl;
	}
	for (auto R : rels3) cerr << R << endl;

	if (!solve(n - 1, sz(rels3), rels3, I)) return false;

	T hi = numeric_limits<T>::infinity(), lo = -hi;

	for (int i : l)
	{
		auto L = rels[i];
		auto la = L.a[n - 1];
		L.a /= la;
		L.b /= la;
		T cur = L.b;
		rep(k, 0, n - 1)
			cur -= L.a[k] * I[k];
		lo = max(lo, cur);
	}
	for (int i : r)
	{
		auto L = rels[i];
		auto la = L.a[n - 1];
		L.a /= la;
		L.b /= la;
		T cur = L.b;
		rep(k, 0, n - 1)
			cur -= L.a[k] * I[k];
		hi = min(hi, cur);
	}
	//lo = ceil(max(lo - E, (T)INT_MIN));
	//hi = floor(min(hi + E, (T)INT_MAX));
	if (lo > hi + E)
		return false;
	//assert(lo <= hi + E);
	//cerr << n << ' ' << lo << ' ' << hi << endl;
	I[n - 1] = max(min(round((lo + hi) / 2), 3e9l), -3e9l);
	return true;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	//cin.exceptions(cin.failbit);

	int n = 0, m = 0;
	vector<rel> rels;
	char cd;
	while (cin >> cd)
	{
		if (cd == 'V')
		{
			char nm;
			cin >> nm;
			varid[nm] = n++;
			varname.push_back(nm);
		}
		else if (cd == '#') break;
		else
		{
			rel r(n);
			rep(i, 0, n)
				cin >> r.a[i];
			string op;
			cin >> op;
			cin >> r.b;
			if (op[0] == '<')
			{
				r.a *= -1;
				r.b *= -1;
			}
			rels.push_back(move(r));
			m++;
		}
	}

	vector<T> I(n);
	for (auto R : rels) cerr << R << endl;
	bool ans = solve(n, m, rels, I);
	if (ans)
		rep(i, 0, n)
		cout << varname[i] << " := " << fixed << setprecision(0) << I[i] << '\n';
	else
		cout << "No solution\n";

	//mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
	//uniform_int_distribution<int> distr(0, n - 1);
	//for (int i = 0; i < n; i++)
	//{
	//	vector<int> l, o, r;
	//	rep(j, 0, sz(rels))
	//	{
	//		auto a = 
	//	}
	//}
}

// g++ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out