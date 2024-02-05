#include <bits/stdc++.h>

using namespace std;

struct v2
{
	int64_t	  x, y;
	friend v2 operator-(const v2 &l, const v2 &r)
	{
		return {l.x - r.x, l.y - r.y};
	}
	friend int64_t operator*(const v2 &l, const v2 &r)
	{
		return l.x * r.x + l.y * r.y;
	}
	friend int64_t operator^(const v2 &l, const v2 &r)
	{
		return l.x * r.y - l.y * r.x;
	}
	friend v2 dc(const v2 &l, const v2 &r)
	{
		return {l * r, l ^ r};
	}
	friend v2 operator*(const v2 &l, int64_t r)
	{
		return {l.x * r, l.y * r};
	}
	int64_t m2() const
	{
		return *this * *this;
	}
	friend istream &operator>>(istream &strm, v2 &v)
	{
		return strm >> v.x >> v.y;
	}
	friend bool operator!=(const v2 &l, const v2 &r)
	{
		return l.x != r.x || l.y != r.y;
	}
};

//<(a - a0) . da, (a - a0) x da> / |da|^2 =? <(b - b0) . db, (b - b0) x db} / |db|^2

int main()
{
	int n;
	while (cin >> n && n)
	{
		vector<v2> A(n), B(n);
		for (v2 &a : A)
			cin >> a;
		for (v2 &b : B)
			cin >> b;
		v2		a0 = A[0], da = A[1] - a0, b0 = B[0], db = B[1] - b0;
		int64_t am2 = da.m2(), bm2 = db.m2();
		for (int i = 0; i < n; i++)
		{
			if (dc(A[i] - a0, da) * bm2 != dc(B[i] - b0, db) * am2)
			{
				cout << "dis";
				break;
			}
		}
		cout << "similar\n";
	}
}
