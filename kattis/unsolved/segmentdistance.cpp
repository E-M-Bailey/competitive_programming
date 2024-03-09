#include <bits/stdc++.h>

using namespace std;

struct v2
{
	float x, y;
	friend v2 &operator-=(v2 &a, v2 b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}
	friend v2 operator-(v2 a, v2 b)
	{
		return a -= b;
	}
	friend float operator*(v2 a, v2 b)
	{
		return a.x * b.x + a.y * b.y;
	}
	friend float operator^(v2 a, v2 b)
	{
		return a.x * b.y - a.y * b.x;
	}
	friend float norm2(v2 a)
	{
		return a * a;
	}
	friend float norm(v2 a)
	{
		return sqrt(norm2(a));
	}
	friend float dist(v2 a, v2 b)
	{
		return norm(b - a);
	}
	friend istream &operator>>(istream &is, v2 &p)
	{
		return is >> p.x >> p.y;
	}
	operator bool() const
	{
		return x || y;
	}
};

struct seg
{
	v2 a, b, d;
	friend istream &operator>>(istream &is, seg &s)
	{
		is >> s.a >> s.b;
		s.d = s.b - s.a;
		return is;
	}
	friend int side(seg a, v2 b)
	{
		float ans = a.d ^ (b - a.a);
		return ans < 0 ? -1 : ans == 0 ? 0 : 1;
	}
	friend bool cross(seg a, seg b)
	{
		return side(a, b.a) * side(a, b.b) <= 0 && side(b, a.a) * side(b, a.b) <= 0;
	}
	friend bool to_side(seg a, v2 b)
	{
		float dp = a.d * (b - a.a);
		return 0 <= dp && dp <= a.d * a.d;
	}
	friend float dist(seg a, v2 b)
	{
		if (to_side(a, b))
			return abs(a.d ^ (b - a.a)) / norm(a.d);
		else
			return min(dist(a.a, b), dist(a.b, b));
	}
	friend float dist(v2 a, seg b)
	{
		return dist(b, a);
	}
	friend float dist(seg a, seg b)
	{
		if (!a.d && !b.d)
			return dist(a.a, b.a);
		else if (!a.d)
			return dist(a.a, b);
		else if (!b.d)
			return dist(a, b.a);
		else if (cross(a, b))
			return 0;
		else
			return min({
				dist(a, b.a),
				dist(a, b.b),
				dist(a.a, b),
				dist(a.b, b)
				});
	}

};

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		seg a, b;
		cin >> a >> b;
		float ans = dist(a, b);
		if (ans < 0 || !finite(ans))
			exit(-1);
		cout << fixed << setprecision(2) << ans << '\n';
	}
}