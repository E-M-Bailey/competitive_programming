#include <bits/stdc++.h>
using namespace std;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> struct point
{
	typedef point P;
	T x, y;
	explicit P(T x = 0, T y = 0): x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T dist2() const { return dot(*this); }
	double dist() const { return sqrt(dist2()); }
	double angle() const { return atan2(y, x); }

};

typedef point<int64_t> P;
vector<P> convexHull(vector<P> pts)
{
	if (size(pts) <= 1) return pts;
	sort(begin(pts), end(pts));
	vector<P> h(size(pts) + 1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(begin(pts), end(pts)))
		for (P p : pts)
		{
			while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
			h[t++] = p;
		}
	return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1]) };
}

int main()
{

}