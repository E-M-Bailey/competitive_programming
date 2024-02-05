#include <bits/stdc++.h>

using namespace std;

typedef long double T;

struct line
{
	mutable T k, m, p;
	bool	  operator<(const line &o) const
	{
		return k < o.k;
	}
	bool operator<(T x) const
	{
		return p < x;
	}
};

struct lct : multiset<line, less<>>
{
	static const T inf;
	T			   div(T a, T b) const
	{
		return a / b;
	}
	bool isect(iterator x, iterator y)
	{
		if (y == end())
			return x->p = inf, 0;
		if (x->k == y->k)
			x->p = x->m > y->m ? inf : -inf;
		else
			x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(T k, T m)
	{
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z))
			z = erase(z);
		if (x != begin() && isect(--x, y))
			isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	T query(T x)
	{
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

const T lct::inf = numeric_limits<T>::infinity();

int main()
{
	T	t, c;
	int n;
	cin >> t >> n >> c;
	lct L;
	L.add(-1, 0);
	for (int i = 0; i < n; i++)
	{
		T tt, x, y;
		cin >> tt >> x >> y;
		T k = y / x, m = -L.query(tt);
		m += c - tt * k;
		L.add(-k, -m);
	}
	T lo = t, hi = t * 1e4;
	for (int i = 0; i < 40; i++)
	{
		T mid = (lo + hi) / 2;
		if (-L.query(mid) > t)
			hi = mid;
		else
			lo = mid;
	}

	cout << fixed << setprecision(7) << (hi + lo) / 2;
}
