#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef complex<ld> cld;

ld const EPS = 1e-15l;

vector<cld> quadratic(cld A, cld B, cld C)
{
	if (abs(A) < EPS)
		return abs(B) < EPS ? vector<cld>{} : vector<cld>{-C / B};
	cld d = B * B - 4.l * A * C;
	cld r = sqrt(d);
	return {(-B - r) / (2.l * A), (-B + r) / (2.l * A)};
}

cld const w3 = cld(-1, sqrt(3)) / 2.l;

cld cbrt(cld z)
{
	return pow(z, 1.l / 3);
}

// x^3 + ax + b = 0
vector<cld> cubic(cld a, cld b)
{
	a /= 3;
	b /= 2;
	cld R = sqrt(b * b + a * a * a);
	cld A = cbrt(-b + R), B = cbrt(-b - R);

	return {A + B, A * w3 + B * w3 * w3, A * w3 * w3 + B * w3};
}

// x^3 + Bx^2 + Cx + D = 0
vector<cld> cubic(cld B, cld C, cld D)
{
	B /= 3.l;
	cld			a	= C - 3.l * B * B;
	cld			b	= 2.l * B * B * B - B * C + D;
	vector<cld> ans = cubic(a, b);
	for (cld &x : ans)
		x -= B;
	return ans;
}

// Ax^3 + Bx^2 + Cx + D = 0
vector<cld> cubic(cld A, cld B, cld C, cld D)
{
	if (abs(A) < EPS)
		return quadratic(B, C, D);
	else
		return cubic(B / A, C / A, D / A);
}

// x^4 + ax^2 + bx + c = 0
vector<cld> quartic(cld a, cld b, cld c)
{
	if (abs(b) < EPS)
	{
		vector<cld> X = quadratic(1., a, c), ans;
		for (cld x : X)
		{
			ans.push_back(sqrt(x));
			ans.push_back(-sqrt(x));
		}
		return ans;
	}

	cld y = cubic(2.l, -a, -2.l * c, a * c - b * b / 4.l)[0];
	cld p = (2.l * y - a) / 4.l, P = sqrt(p), q = (-2.l * y - a) / 4.l, r = (b / P) / 4.l;
	cld QpR = sqrt(q + r), QmR = sqrt(q - r);
	return {-P + QpR, -P - QpR, P + QmR, P - QmR};
}

// x^4 + Bx^3 + Cx^2 + Dx + E = 0
vector<cld> quartic(cld B, cld C, cld D, cld E)
{
	B /= 4;
	cld			a	= C - 6.l * B * B;
	cld			b	= 8.l * B * B * B - 2.l * B * C + D;
	cld			c	= -3.l * B * B * B * B + C * B * B - B * D + E;
	vector<cld> ans = quartic(a, b, c);
	for (cld &x : ans)
		x -= B;
	return ans;
}

// Ax^4 + Bx^3 + Cx^2 + Dx + E = 0
vector<cld> quartic(cld A, cld B, cld C, cld D, cld E)
{
	if (abs(A) < EPS)
		return cubic(B, C, D, E);
	else
		return quartic(B / A, C / A, D / A, E / A);
}

// From KACTL
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
	bool operator<(P p) const
	{
		return tie(x, y) < tie(p.x, p.y);
	}
	bool operator==(P p) const
	{
		return tie(x, y) == tie(p.x, p.y);
	}
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
	T dot(P p) const
	{
		return x * p.x + y * p.y;
	}
	T cross(P p) const
	{
		return x * p.y - y * p.x;
	}
	T cross(P a, P b) const
	{
		return (a - *this).cross(b - *this);
	}
	T dist2() const
	{
		return x * x + y * y;
	}
	ld dist() const
	{
		return sqrt((ld)dist2());
	}
	// angle to x−axis in interval [−pi , pi ]
	ld angle() const
	{
		return atan2(y, x);
	}
	P unit() const
	{
		return *this / dist();
	} // makes dist ()=1
	P perp() const
	{
		return P(-y, x);
	} // rotates +90 degrees
	P normal() const
	{
		return perp().unit();
	}
	// returns point rotated ’a’ radians ccw around the origin
	P rotate(ld a) const
	{
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	friend ostream &operator<<(ostream &os, P p)
	{
		return os << "(" << p.x << "," << p.y << ")";
	}
};
typedef Point<ld> P;
ld				  segDist(P s, P e, P p)
{
	if (s == e)
		return (p - s).dist();
	auto d = (e - s).dist2(), t = min(d, max(0.l, (p - s).dot(e - s)));
	return ((p - s) * d - (e - s) * t).dist() / d;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(8);

	int tc;
	cin >> tc;
	while (tc--)
	{
		ld xa, ya, xb, yb, xc, yc, r;
		cin >> xa >> ya >> xb >> yb >> xc >> yc >> r;
		if (r == 0)
		{
			cout << hypot(xa - xc, ya - yc) + hypot(xb - xc, yb - yc) << '\n';
			continue;
		}
		if (segDist(P{xa, ya}, P{xb, yb}, P{xc, yc}) <= r + EPS)
		{
			cout << hypot(xa - xb, ya - yb) << '\n';
			continue;
		}
		xa = (xa - xc) / r;
		ya = (ya - yc) / r;
		xb = (xb - xc) / r;
		yb = (yb - yc) / r;

		ld A = xa * yb + xb * ya;
		ld B = xa * xb - ya * yb;
		ld C = xa + xb;
		ld D = ya + yb;

		ld c4 = 4 * (A * A + B * B);
		ld c3 = -4 * (A * D + B * C);
		ld c2 = C * C + D * D - c4;
		ld c1 = -2 * A * D - c3;
		ld c0 = A * A - C * C;

		auto roots = quartic(c4, c3, c2, c1, c0);
		ld	 ans   = numeric_limits<ld>::infinity();
		for (auto &x : roots)
		{
			if (abs(imag(x)) >= EPS)
				continue;
			ld X = real(x);
			ld Y = sqrt(1 - X * X);
			ans	 = min(ans, hypot(X - xa, Y - ya) + hypot(X - xb, Y - yb));
			ans	 = min(ans, hypot(X - xa, Y + ya) + hypot(X - xb, Y + yb));
		}

		cout << ans * r << '\n';
	}
}
