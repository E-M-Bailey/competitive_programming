#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

const int LIM = 1e5;

struct seg
{
	int x1, y1, x2, y2;

	seg(int X1, int Y1, int X2, int Y2) :
		x1(X1),
		y1(Y1),
		x2(X2),
		y2(Y2)
	{
		if (x1 > x2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
	}

	seg(pair<int, int> p1, pair<int, int> p2) :
		seg(p1.first, p1.second, p2.first, p2.second)
	{}

	double operator()(double x) const
	{
		return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
	}

	friend bool operator<(const seg &l, const seg &r)
	{
		int lo = max(l.x1, r.x1), hi = min(l.x2, r.x2);
		double x = 0.5 * (lo + hi);
		return lo <= hi && l(x) < r(x);
	}
};

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	vector<pair<int, int>> pts;
	int X, Y;
	while (cin >> X >> Y)
		pts.emplace_back(X, Y);

	vector<seg> S;
	for (int i = 0; i < (int)pts.size(); i++)
		if (pts[i].first != pts[(i + 1) % pts.size()].first)
			S.emplace_back(pts[i], pts[(i + 1) % pts.size()]);

	int n = (int)S.size();

	vector<vector<bool>> LT(n, vector<bool>(n));
	vector<int> CT(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j)
				CT[j] += (LT[i][j] = S[i] < S[j]);

	//for (int i = 0; i < n; i++)
	//	cerr << i << ' ' << S[i].x1 << ' ' << S[i].y1 << ' ' << S[i].x2 << ' ' << S[i].y2 << ' ' << CT[i] << endl;

	long long ans = 0;
	vector<int> H(LIM, -1);

	//long long cd = 0;

	for (int i = 0; i < n; i++)
	{
		//cd = ans;
		int idx = -1;
		for (int j = 0; idx < 0; j++)
			if (CT[j] == 0)
				idx = j;
		for (int j = 0; j < n; j++)
			if (j != idx)
				CT[j] -= LT[idx][j];

		auto [x1, y1, x2, y2] = S[idx];
		long long dx = x2 - x1;
		long long dy = y2 - y1;
		int plo = y1, phi = y1;
		for (int x = x1, rx = 1; x < x2; x++, rx++)
		{
			int lo = int((rx * dy + y1 * dx) / dx);
			int hi = int((rx * dy + (y1 + 1) * dx - 1) / dx);
			//cerr << '*' << lo << ' ' << hi << endl;
			if (H[x] < 0)
			{
				H[x] = max(phi, hi);
				//cerr << ' ' << phi << ' ' << hi << endl;
			}
			else
			{
				int del = min(plo, lo) - H[x];
				if (del > 0)
					ans += del;
				//cerr << ' ' << x << ' ' << min(plo, lo) << ' ' << H[x] << '\n';
				H[x] = -1;
			}
			plo = lo;
			phi = hi;
		}
		//cerr << idx << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << ans - cd << endl;
		CT[idx] = -1;
	}

	cout << ans;
}

//
//#pragma GCC optimize("O3")
//typedef long long ll;
//
//ll cmp_rat(pair<ll, ll> a, pair<ll, ll> b)
//{
//	if (a.second < 0)
//	{
//		a.first = -a.first;
//		a.second = -a.second;
//	}
//	if (b.second < 0)
//	{
//		b.first = -b.first;
//		b.second = -b.second;
//	}
//	return a.first * b.second - a.second * b.first;
//}
//
//struct seg
//{
//	ll x, y, dx, dy;
//	seg(ll x1, ll y1, ll x2, ll y2) :
//		x(x1),
//		y(y1),
//		dx(x2 - x1),
//		dy(y2 - y1)
//	{}
//	pair<ll, ll> operator()(ll X) const
//	{
//		if (dx > 0)
//			return { y * dx + (X - x) * dy, dx };
//		else
//			return { -(y * dx + (X - x) * dy), -dx };
//	}
//	ll x1() const
//	{
//		return dx > 0 ? x : x + dx;
//	}
//	ll y1() const
//	{
//		return dx > 0 ? y : y + dy;
//	}
//	bool incr() const
//	{
//		return dx * dy > 0;
//	}
//	friend bool operator<(seg const &l, seg const &r)
//	{
//		ll x = max(l.x1(), r.x1());
//		//cerr << "  " << l << ' ' << nl << ' ' << dl << endl;
//		//cerr << "  " << r << ' ' << nr << ' ' << dr << endl;
//		ll c = cmp_rat(l(x), r(x));
//		if (c)
//			return c < 0;
//		else
//			return cmp_rat(l(x + 1), r(x + 1)) < 0;
//	}
//	friend ostream &operator<<(ostream &os, seg const &s)
//	{
//		return os << '(' << s.x << ',' << s.y << ")-(" << s.x + s.dx << ',' << s.y + s.dy << ')';
//	}
//};
//
//ll n, m;
//vector<seg> S;
//
//struct event
//{
//	ll id;
//	explicit event(ll idx) :
//		id(idx)
//	{}
//	ll i() const
//	{
//		return id;
//	}
//	ll j() const
//	{
//		return (id + 1) % m;
//	}
//	seg &si() const
//	{
//		return S[i()];
//	}
//	seg &sj() const
//	{
//		return S[j()];
//	}
//	bool ei() const
//	{
//		return si().dx > 0;
//	}
//	bool ej() const
//	{
//		return sj().dx < 0;
//	}
//	ll x() const
//	{
//		return S[j()].x;
//	}
//	friend bool operator<(event const &l, event const &r)
//	{
//		return l.x() < r.x();
//	}
//};
//
//vector<event> E;
//
//struct entry
//{
//	ll i, j, x;
//	entry(ll I, ll J, ll X) :
//		i(I),
//		j(J),
//		x(X)
//	{}
//	seg &si() const
//	{
//		return S[i];
//	}
//	seg &sj() const
//	{
//		return S[j];
//	}
//};
//
//auto const I_cmp = [](ll i, ll j)
//{
//	return S[i] < S[j];
//};
//
//map<ll, entry, decltype(I_cmp)> I(I_cmp);
//
//void add(ll i, ll j, ll x)
//{
//	//cerr << " Inserting " << S[i] << ' ' << S[j] << ' ' << x << endl;
//	I.emplace(j, entry(i, j, x));
//}
//
//ll fdiv(ll num, ll den);
//
//ll cdiv(ll num, ll den)
//{
//	if (num < 0)
//	{
//		num = -num;
//		den = -den;
//	}
//	return den > 0 ? (num + den - 1) / den : -(num / -den);
//}
//
//ll fdiv(ll num, ll den)
//{
//	if (num < 0)
//	{
//		num = -num;
//		den = -den;
//	}
//	return den > 0 ? num / den : -((num - den - 1) / -den);
//}
//ll fdiv(pair<ll, ll> x)
//{
//	return fdiv(x.first, x.second);
//}
//ll cdiv(pair<ll, ll> x)
//{
//	return cdiv(x.first, x.second);
//}
//
//ll on_under(ll dx, ll dy, ll x1, ll x2)
//{
//	if (dx * dy == 0)
//		return 0;
//	if (dx < 0)
//	{
//		dx = -dx;
//		x1 = dx - x1;
//		x2 = dx - x2;
//	}
//	if (dy < 0)
//	{
//		dy = -dy;
//		x1 = dx - x1;
//		x2 = dx - x2;
//	}
//	if (x1 > x2)
//		swap(x1, x2);
//	ll y1 = fdiv(dy * x1, dx), y2 = cdiv(dy * x2, dx);
//	ll g = dx / gcd(dx, dy);
//	ll a = fdiv(x1, g) + 1, b = cdiv(x2, g) - 1;
//	ll on = (x2 - x1) + (y2 - y1) - (b - a + 2);
//	//cerr << "  " << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << ' ' << a << ' ' << b << ' ' << ((x2 - x1) * (y2 - y1) + on) / 2 << endl;
//	//cerr << ' ' << (x2 - x1) * (y2 - y1) << ' ' << on << endl;
//	//cerr << "  " << on << endl;
//	return ((x2 - x1) * (y2 - y1) + on) / 2;
//}
//
//ll cell_ct(ll i, ll j, ll x1, ll x2)
//{
//	if (S[j] < S[i])
//		swap(i, j);
//	seg const &si = S[i], &sj = S[j];
//
//	ll y1 = min(fdiv(si(x1)), fdiv(si(x2)));
//	ll y2 = max(cdiv(sj(x1)), cdiv(sj(x2)));
//
//	//cerr << si << ' ' << sj << ' ' << x1 << ' ' << x2 << endl;
//	ll oui = on_under(si.dx, si.dy, x1 - si.x1(), x2 - si.x1()), ouj = on_under(sj.dx, sj.dy, x1 - sj.x1(), x2 - sj.x1());
//
//	//cerr << ' ' << (y2 - y1) * (x2 - x1) << ' ' << oui << ' ' << ouj << ' ' << (y2 - y1) * (x2 - x1) - oui - ouj << endl;
//	return (y2 - y1) * (x2 - x1) - oui - ouj;
//	//return
//		/*
//		if (S[j] < S[i])
//			swap(i, j);
//		ll ans = 0;
//		for (ll x = x1; x < x2; x++)
//		{
//			auto [ni, di] = si(si.incr() ? x + 1 : x);
//			auto [nj, dj] = sj(sj.incr() ? x : x + 1);
//			//if (x == x1)
//			//	cerr << fdiv(nj, dj) << ' ' << cdiv(ni, di) << endl;
//			ans += fdiv(nj, dj) - cdiv(ni, di);
//		}
//		return ans;
//		*/
//}
//
//int main(int argc, char const *argv[])
//{
//	if (argc > 1)
//	{
//		ignore = freopen(argv[1], "r", stdin);
//		ignore = freopen(argv[2], "w", stdout);
//	}
//
//	{
//		vector<pair<ll, ll>> XY;
//		ll x, y;
//		while (cin >> x >> y)
//			XY.emplace_back(x, y);
//		n = XY.size();
//
//		for (ll i = 0; i < n; i++)
//		{
//			auto [x1, y1] = XY[i];
//			auto [x2, y2] = XY[(i + 1) % n];
//			if (x1 != x2)
//				S.emplace_back(x1, y1, x2, y2);
//		}
//		m = S.size();
//	}
//
//	E.reserve(m);
//	for (ll i = 0; i < m; i++)
//		E.emplace_back(i);
//	sort(begin(E), end(E));
//
//
//	ll ans = 0;
//	for (event e : E)
//	{
//		ll i = e.i(), j = e.j(), x = e.x();
//		//cerr << "processing " << S[i] << ", " << S[j] << ' ' << x << ' ' << e.ei() << ' ' << e.ej() << endl;
//
//		if (e.ei() && e.ej())
//		{
//			//cerr << " Case A " << endl;
//			if (S[j] < S[i])
//				swap(i, j);
//			auto it = I.lower_bound(i);
//			auto jt = next(it);
//			auto [pi, pj, px] = it->second;
//			I.erase(it);
//			if (pi == i)
//			{
//				ans += cell_ct(pi, pj, px, x);
//			}
//			else // pj == i
//			{
//				auto [qi, qj, qx] = jt->second;
//				I.erase(jt);
//				ans += cell_ct(pi, pj, px, x);
//				ans += cell_ct(qi, qj, qx, x);
//				add(pi, qj, x);
//			}
//		}
//		else if (e.ei() || e.ej())
//		{
//			//cerr << " Case B " << endl;
//			if (e.ej())
//				swap(i, j);
//			auto it = I.lower_bound(i);
//			auto [pi, pj, px] = it->second;
//			//cerr << "  " << pi << ' ' << pj << ' ' << px << endl;
//			I.erase(it);
//			ans += cell_ct(pi, pj, px, x);
//			if (pi == i)
//			{
//				add(j, pj, x);
//			}
//			else // pj == i
//			{
//				add(pi, j, x);
//			}
//		}
//		else
//		{
//			//cerr << " Case C " << endl;
//			if (S[j] < S[i])
//				swap(i, j);
//			auto it = I.lower_bound(i);
//			if (it == I.end() || e.si() < it->second.si())
//			{
//				add(i, j, x);
//			}
//			else
//			{
//				auto [pi, pj, px] = it->second;
//				I.erase(it);
//				ans += cell_ct(pi, pj, px, x);
//				add(pi, i, x);
//				add(j, pj, x);
//			}
//		}
//	}
//
//	cout << ans;
//}