#include <bits/stdc++.h>

using namespace std;

typedef long double T;

T det2(T a, T b, T c, T d)
{
	return a * d - b * c;
}

struct v3
{
	T x, y, z;
};

v3 operator+(v3 a, v3 b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

v3 operator-(v3 a, v3 b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

T operator*(v3 a, v3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

v3 operator^(v3 a, v3 b)
{
	return { det2(a.y, a.z, b.y, b.z), det2(a.z, a.x, b.z, b.x), det2(a.x, a.y, b.x, b.y) };
}

v3 operator*(v3 a, T b)
{
	return { a.x * b, a.y * b, a.z * b };
}

istream &operator>>(istream &is, v3 &a)
{
	return is >> a.x >> a.y >> a.z;
}

ostream &operator<<(ostream &os, v3 a)
{
	return os << '(' << a.x << ',' << a.y << ',' << a.z << ')' << endl;
}

struct tri
{
	v3 a, b, c;
};

v3 norm(tri const &t)
{
	v3 ab = t.b - t.a, bc = t.c - t.b;
	return ab ^ bc;
}

void point_out(v3 c, tri &t)
{
	//cerr << t.a << ' ' << t.b << ' ' << t.c << endl;
	//cerr << (t.b - c)
	if ((t.b - c) * norm(t) < 0)
		swap(t.a, t.c);
}

T vol_with_0(tri const &t)
{
	T vol = t.a * (t.b ^ t.c) / 6;
	//cerr << t.a << ' ' << t.b << ' ' << t.c << ' ' << vol;
	return vol;
}

int main()
{
	cout << fixed << setprecision(2);
	cerr << fixed << setprecision(2);

	int n;
	cin >> n;
	T ans = 0;
	while (n--)
	{
		T cur = 0;
		int f;
		cin >> f;
		int tv = 0;
		v3 c{ 0, 0, 0 };
		vector<vector<v3>> faces(f);
		for (auto &face : faces)
		{
			int v;
			cin >> v;
			face.resize(v);
			for (v3 &vert : face)
			{
				cin >> vert;
				c = c + vert;
			}
			tv += v;
		}
		c = c * (T(1) / tv);
		cerr << "center: " << c.x << ' ' << c.y << ' ' << c.z << endl;
		for (auto const &face : faces)
		{
			for (int i = 2; i < (int)face.size(); i++)
			{
				tri t{ face[0], face[i - 1], face[i] };
				point_out(c, t);
				cur += vol_with_0(t);
			}
		}
		ans += abs(cur);
	}
	cout << fixed << setprecision(2) << ans;
}

/*
1
6
4 0 0 0 0 0 1 0 1 1 0 1 0
4 0 0 0 0 0 1 1 0 1 1 0 0
4 0 0 0 0 1 0 1 1 0 1 0 0
4 1 1 1 1 1 0 1 0 0 1 0 1
4 1 1 1 1 1 0 0 1 0 0 1 1
4 1 1 1 1 0 1 0 0 1 0 1 1
*/

/*
1
4
3 0 0 0 0 0 1 0 1 0
3 0 0 0 0 0 1 1 0 0
3 0 0 0 0 1 0 1 0 0
3 0 0 1 0 1 0 1 0 0
*/