#include <bits/stdc++.h>

using namespace std;

template<class T>
struct pt
{
	T x, y;
	pt() = default;
	pt(T x, T y): x(x), y(y) {}
	friend pt operator+(const pt& l, const pt& r)
	{
		return { l.x + r.x, l.y + r.y };
	}
	friend pt operator-(const pt& l, const pt& r)
	{
		return { l.x - r.x, l.y - r.y };
	}
	friend T operator*(const pt& l, const pt& r)
	{
		return l.x * r.x + l.y * r.y;
	}
	friend pt operator*(T l, const pt& r)
	{
		return { l * r.x, l * r.y };
	}
	friend pt operator*(const pt& l, T r)
	{
		return { l.x * r, l.y * r };
	}
	friend pt operator/(const pt& l, T r)
	{
		return { l.x / r, l.y / r };
	}
	friend T mag2(const pt& p)
	{
		return p * p;
	}
	friend T mag(const pt& p)
	{
		return sqrtl(mag2(p));
	}
	friend T dist(const pt& a, const pt& b)
	{
		return mag(a - b);
	}
	friend istream& operator>>(istream& l, pt& r)
	{
		return l >> r.x >> r.y;
	}
	friend ostream& operator<<(ostream& l, const pt& r)
	{
		return l << '(' << r.x << ", " << r.y << ')';
	}
	friend bool operator==(const pt& a, const pt& b)
	{
		return a.x == b.x && a.y == b.y;
	}
};

template<class T>
long double min_mag2(pt<T> p, pt<T> r, T t)
{
	//cerr << "min_mag2: " << p << ' ' << r << ' ' << t << " -> ";
	long double ans = min(mag2(p), mag2(p + r * t));
	if (abs(r * p) >= 1e-8)
	{
		long double tau = -(r * r) / (r * p);
		//cerr << mag2(p) << ' ' << mag2(p + r * t) << ' ';
		if (0 < tau && tau < t)
		{
			ans = min(ans, mag2(p + r * tau));
			//cerr << tau << ' ' << mag2(p + r * tau) << ' ';
		}
	}
	//cerr << ans << endl;
	return ans;
}

template<class T>
long double min_dist(pt<T> a1, pt<T> da, pt<T> b1, pt<T> db, T t)
{
	return sqrtl(min_mag2(a1 - b1, da - db, t));
}

typedef pt<long double> pnt;

struct path
{
	queue<pnt> P;
	queue<pnt> D;
	queue<long double> T;
	long double t;

	friend istream& operator>>(istream& a, path& b)
	{
		auto& [P, D, T, t] = b;
		t = 0;
		int n;
		a >> n;
		pnt prev;
		a >> prev;
		P.push(prev);
		for (int i = 1; i < n; i++)
		{
			pnt cur;
			a >> cur;
			P.push(cur);
			pnt d = cur - prev;
			D.push(d);
			T.push(mag(d));
			prev = cur;
		}

		return a;
	}

	long double rem()
	{
		return T.front() - t;
	}

	void adv(long double dt)
	{
		t += dt;
		if (t >= T.front())
		{
			t -= T.front();
			P.pop();
			D.pop();
			T.pop();
		}
		
	}

	operator bool() const
	{
		return size(D);
	}

};

int main(int argc, const char* argv[])
{
	if (argc >= 3)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int n, m;
	cin >> n;
	vector<pnt> A(n);
	for (pnt& a : A)
		cin >> a;
	cin >> m;
	vector<pnt> B(m);
	for (pnt& b : B)
		cin >> b;
	vector<pnt> DA(n - 1), DB(m - 1);
	vector<long double> TA(n - 1), TB(m - 1);
	for (int i = 1; i < n; i++)
	{
		TA[i - 1] = mag(DA[i - 1] = A[i] - A[i - 1]);
		DA[i - 1] = DA[i - 1] / TA[i - 1];
	}
	for (int i = 1; i < m; i++)
	{
		TB[i - 1] = mag(DB[i - 1] = B[i] - B[i - 1]);
		DB[i - 1] = DB[i - 1] / TB[i - 1];
	}

	/*for (auto a : A)
		cerr << a << ' ';
	cerr << endl;
	for (auto a : DA)
		cerr << a << ' ';
	cerr << endl;*/

	int i = 0, j = 0;
	long double ta = 0, tb = 0;
	long double ans = dist(A[0], B[0]);
	while (i < n - 1 && j < m - 1)
	{
		pnt a = A[i] + DA[i] * ta;
		pnt b = B[j] + DB[j] * tb;
		long double dta = TA[i] - ta, dtb = TB[j] - tb;
		long double dt;
		//cerr << DA[i] << ' ' << ta << a << ' ' << b << ' ' << ta << ' ' << tb << ' ' << dta << ' ' << dtb << endl;
		pnt da = DA[i], db = DB[j];
		if (dta <= dtb)
		{
			dt = dta;
			ta = 0;
			tb += dt;
			i++;
		}
		else
		{
			dt = dtb;
			ta += dt;
			tb = 0;
			j++;
		}
		if (dt <= 1e-10) continue;
		long double cur = min_dist(a, da, b, db, dt);
		//cerr << ' ' << dt << ' ' << cur << endl;
		ans = min(ans, cur);
	}
	cout << setprecision(6) << ans << endl;

}