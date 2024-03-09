#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define sz(x) int(size(x))
#define all(x) begin(x), end(x)

// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/Point.h
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point
{
	typedef Point P;
	T x, y;
	int i;
	explicit Point(T x = 0, T y = 0, int i = -1) : x(x), y(y), i(i) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y, i); }
	P operator-(P p) const { return P(x - p.x, y - p.y, i); }
	P operator*(T d) const { return P(x * d, y * d, i); }
	P operator/(T d) const { return P(x / d, y / d, i); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const
	{
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	friend ostream &operator<<(ostream &os, P p)
	{
		return os << "(" << p.x << "," << p.y << ")";
	}
};

// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ConvexHull.h
typedef Point<ll> P;
vector<P> convexHull(vector<P> pts)
{
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts) + 1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts)
		{
			while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
			h[t++] = p;
		}
	return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1]) };
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<P> pts(n);
	for (int i = 0; i < n; i++)
		pts[i].i = i;
	for (auto &[x, y, i] : pts)
		cin >> x;
	for (auto &[x, y, i] : pts)
		cin >> y;

	P tgt;
	cin >> tgt.x >> tgt.y;

	vector<long double> ans(n);

	pts = convexHull(pts);
	n = sz(pts);
	auto origin = pts[0];
	for (auto &p : pts)
		p = p - origin;
	tgt = tgt - origin;

	if (n == 1)
	{
		if (tgt.dist2() == 0)
			ans[pts[0].i] = 1;
		else
			ans.clear();
	}
	else if (n == 2)
	{
		auto dp = pts[1], dt = tgt;
		if (dp.cross(dt) == 0)
		{
			long double p1 = (long double)dp.dot(dt) / dp.dot(dp);
			ans[pts[0].i] = 1 - p1;
			ans[pts[1].i] = p1;
		}
		else
			ans.clear();
	}
	else
	{
		bool fnd = false;
		for (int i = 1; i < n - 1; i++)
		{
			auto a = pts[i], b = pts[i + 1];
			if (a.cross(tgt) >= 0 && b.cross(tgt) <= 0 && (b - a).cross(tgt - a) >= 0)
			{
				fnd = true;
				Point<long double> A(pts[0].x, pts[0].y, pts[0].i), B(a.x, a.y, a.i), C(b.x, b.y, b.i);
				long double xx = (long double)a.dot(tgt) / a.dot(a);
				long double yy = (long double)a.cross(tgt) / a.dot(a);
			}
		}
		if (!fnd)
			ans.clear();
	}

	cout << fixed << setprecision(7);
}