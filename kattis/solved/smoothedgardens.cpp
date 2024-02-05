#include <bits/stdc++.h>

using namespace std;

typedef long double T;
const T				PI = 4 * atanl(1);

struct vec
{
	T x, y;
	vec(T X = 0, T Y = 0) : x(X), y(Y) {}
	friend vec operator-(const vec &a)
	{
		return {-a.x, -a.y};
	}
	friend vec operator+(const vec &a, const vec &b)
	{
		return {a.x + b.x, a.y + b.y};
	}
	vec &operator+=(const vec &b)
	{
		return *this = *this + b;
	}
	friend vec operator-(const vec &a, const vec &b)
	{
		return {a.x - b.x, a.y - b.y};
	}
	vec &operator-=(const vec &b)
	{
		return *this = *this - b;
	}
	friend vec operator*(const vec &a, T b)
	{
		return {a.x * b, a.y * b};
	}
	friend vec operator*(T a, const vec &b)
	{
		return {a * b.x, a * b.y};
	}
	vec &operator*=(T b)
	{
		return *this = *this * b;
	}
	friend vec operator/(const vec &a, T b)
	{
		return {a.x / b, a.y / b};
	}
	vec &operator/=(T b)
	{
		return *this = *this / b;
	}
	friend T operator*(const vec &a, const vec &b)
	{
		return a.x * b.x + a.y * b.y;
	}
	vec r90() const
	{
		return {-y, x};
	}
	friend T operator^(const vec &a, const vec &b)
	{
		return a.r90() * b;
	}
	T mag2() const
	{
		return *this * *this;
	}
	T mag() const
	{
		return sqrtl(mag2());
	}
	vec norm() const
	{
		return *this / mag();
	}
	T arg() const
	{
		return atan2l(y, x);
	}
	vec rot(T t) const
	{
		T s, c;
		sincosl(t, &s, &c);
		return {c * x - s * y, s * x + c * y};
	}
	friend vec hmul(const vec &a, const vec &b)
	{
		return {a.x * b.x, a.y * b.y};
	}
	friend vec hdiv(const vec &a, const vec &b)
	{
		return {a.x / b.x, a.y / b.y};
	}
	vec from_ortho(const vec &u) const
	{
		return u * x + u.r90() * y;
	}
	vec to_ortho(const vec &u) const
	{
		return {u * *this, u ^ *this};
	}
	friend ostream &operator<<(ostream &os, const vec &v)
	{
		return os << '(' << v.x << ',' << v.y << ')';
	}
};

vec unit(T t)
{
	T s, c;
	sincosl(t, &s, &c);
	return {c, s};
}

T poly(const vector<vec> &A)
{
	T ans = 0;
	for (int i = 0; i < (int)A.size(); i++)
		ans += A[i] ^ A[(i + 1) % A.size()];
	return abs(ans) / 2;
}

struct frame
{
	vec c, u;
	vec map(const vec &v) const
	{
		return v.from_ortho(u) + c;
	}
	vec imap(const vec &v) const
	{
		return (v - c).to_ortho(u);
	}
	vec tmap(const vec &v) const
	{
		return v.from_ortho(u);
	}
	vec itmap(const vec &v) const
	{
		return v.to_ortho(u);
	}
};

struct ellipse
{
	vec	  ab;
	frame f;

	ellipse(const vec &A, const vec &B, T l)
	{
		vec D = (B - A) / 2;
		ab.x  = l / 2;
		ab.y  = sqrtl(ab.x * ab.x - D * D);
		f.c	  = A + D;
		f.u	  = D.norm();
	}

	vec operator()(T t) const
	{
		return f.map(hmul(unit(t), ab));
	}

	T inv(const vec &v) const
	{
		return hdiv(f.imap(v), ab).arg();
	}

	// portion <= 180 degrees
	T sect(const vec &a, const vec &b) const
	{
		T dt = inv(b) - inv(a);
		if (dt < 0)
			dt += 2 * PI;
		if (dt > PI)
			dt = 2 * PI - dt;
		return ab.x * ab.y * dt / 2;
	}

	T seg(const vec &a, const vec &b) const
	{
		return sect(a, b) - poly({a, b, f.c});
	}

	vec isect(const vec &p, const vec &q) const
	{
		vec P = hdiv(f.imap(p), ab);
		vec Q = hdiv(f.itmap(q), ab);
		T	a = Q * Q, b = 2 * P * Q, c = P * P - 1;
		T	s = (-b + sqrtl(b * b - 4 * a * c)) / (2 * a);
		return p + q * s;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int tc;
	cin >> tc;
	while (tc--)
	{
		int k;
		cin >> k;
		cout << k << ' ';

		vec A{}, B{}, C{};
		T	l;
		cin >> B.x >> C.x >> C.y >> l;

		T dab = (B - A).mag(), dac = (C - A).mag(), dbc = (C - B).mag();

		ellipse ab(A, B, l - dac - dbc), ac(A, C, l - dab - dbc), bc(B, C, l - dab - dac);
		ellipse AB(A, B, l - dab), AC(A, C, l - dac), BC(B, C, l - dbc);

		vec a = ab.isect(C, A - C), b = ab.isect(C, B - C), c = bc.isect(A, B - A), d = bc.isect(A, C - A),
			e = ac.isect(B, C - B), f = ac.isect(B, A - B);
		T ans = ab.seg(a, b) + AC.seg(b, c) + bc.seg(c, d) + AB.seg(d, e) + ac.seg(e, f) + BC.seg(f, a) +
				poly({a, b, c, d, e, f});
		cout << fixed << setprecision(3) << ans << '\n';
	}
}
