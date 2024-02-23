#include <bits/stdc++.h>

using namespace std;

template<class T>
int sgn(T x)
{
	return (x > 0) - (x < 0);
}
template<class T>
struct Point
{
	typedef Point P;
	T			  x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	P operator+(P p) const
	{
		return P(x + p.x, y + p.y);
	}
	P operator-(P p) const
	{
		return P(x - p.x, y - p.y);
	}
	P operator*(T d) const
	{
		return P(x * d, y * d);
	}
	P operator/(T d) const
	{
		return P(x / d, y / d);
	}
	T dist2() const
	{
		return x * x + y * y;
	}
	T cross(P p)
	{
		return x * p.y - y * p.x;
	}
	double dist() const
	{
		return sqrt((double)dist2());
	}
	P perp() const
	{
		return P(-y, x);
	}
};

typedef Point<double> P;

double ccRadius(const P &A, const P &B, const P &C)
{
	return (B - A).dist() * (C - B).dist() * (A - C).dist() / abs((B - A).cross(C - A)) / 2;
}

P ccCenter(const P &A, const P &B, const P &C)
{
	P b = C - A, c = B - A;
	return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}

pair<P, double> mec(vector<P> ps)
{
	shuffle(begin(ps), end(ps), mt19937(time(0)));
	P	   o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	for (int i = 0; i < (int)size(ps); i++)
		if ((o - ps[i]).dist() > r * EPS)
		{
			o = ps[i], r = 0;
			for (int j = 0; j < i; j++)
				if ((o - ps[j]).dist() > r * EPS)
				{
					o = (ps[i] + ps[j]) / 2;
					r = (o - ps[i]).dist();
					for (int k = 0; k < j; k++)
						if ((o - ps[k]).dist() > r * EPS)
						{
							o = ccCenter(ps[i], ps[j], ps[k]);
							r = (o - ps[i]).dist();
						}
				}
		}
	return {o, r};
}

double solve(int n, vector<double> const &X, vector<double> const &Y)
{
	vector<P> pts(n);
	for (int i = 0; i < n; i++)
		pts[i] = P(X[i], Y[i]);
	return mec(pts).second;
}

int main()
{
	int n;
	cin >> n;
	vector<double> X(n), Y(n), Z(n);
	for (int i = 0; i < n; i++)
		cin >> X[i] >> Y[i] >> Z[i];
	cout << fixed << setprecision(6) << 2 * min({solve(n, X, Y), solve(n, X, Z), solve(n, Y, Z)});
}
