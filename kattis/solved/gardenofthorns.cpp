#include <bits/stdc++.h>

using namespace std;

// Source: KACTL
template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
	typedef Point P;
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); }
	P perp() const { return P(-y, x); }
	P normal() const { return perp().unit(); }
	P rotate(double a) const
	{
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	friend ostream &operator<<(ostream &os, P p)
	{
		return os << "(" << p.x << "," << p.y << ")";
	}
};

// Source: KACTL
typedef Point<double> P;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P c, double r, vector<P> ps)
{
	auto tri = [&](P p, P q)
	{
		auto r2 = r * r / 2;
		P d = q - p;
		auto a = d.dot(p) / d.dist2(), b = (p.dist2() - r * r) / d.dist2();
		auto det = a * a - b;
		if (det <= 0)
			return arg(p, q) * r2;
		auto s = max(0., -a - sqrt(det)), t = min(1., -a + sqrt(det));
		if (t < 0 || 1 <= s)
			return arg(p, q) * r2;
		P u = p + d * s, v = p + d * t;
		return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
	};
	auto sum = 0.0;
	for (int i = 0; i < (int)size(ps); i++)
		sum += tri(ps[i] - c, ps[(i + 1) % (int)size(ps)] - c);
	return sum;
}

int main()
{
	int n, r, w, h;
	cin >> n >> r >> w >> h;
	double ans = 0;
	vector<P> rect{P{0, 0}, P{w, 0}, P{w, h}, P{0, h}};
	while (n--)
	{
		int x, y, v;
		cin >> x >> y >> v;
		ans += v * circlePoly(P{x, y}, r, rect) / (w * h);
	}
	cout << fixed << setprecision(10) << ans;
}