#include <bits/stdc++.h>

using namespace std;

typedef __float128 T;
const T			   E  = 1e-8Q;
const T			   DT = 1e-7Q;

istream &operator>>(istream &is, __float128 &x)
{
	long double y;
	is >> y;
	x = y;
	return is;
}

ostream &operator<<(ostream &os, __float128 x)
{
	return os << (long double)x;
}

__float128 sqrt(__float128 a)
{
	__float128 x = a;
	for (int i = 0; i < 20; i++)
		x = (x + (a / x)) / 2;
	return x;
}

struct v2
{
	T		  x = 0, y = 0;
	friend v2 operator-(const v2 &a)
	{
		return {-a.x, -a.y};
	}
	friend v2 operator+(const v2 &a, const v2 &b)
	{
		return {a.x + b.x, a.y + b.y};
	}
	friend v2 operator-(const v2 &a, const v2 &b)
	{
		return {a.x - b.x, a.y - b.y};
	}
	friend v2 operator*(const v2 &a, T b)
	{
		return {a.x * b, a.y * b};
	}
	friend v2 operator*(T a, const v2 &b)
	{
		return {a * b.x, a * b.y};
	}
	friend v2 operator/(const v2 &a, T b)
	{
		return {a.x / b, a.y / b};
	}
	v2 &operator+=(const v2 &b)
	{
		return *this = *this + b;
	}
	v2 &operator-=(const v2 &b)
	{
		return *this = *this - b;
	}
	v2 &operator*=(T b)
	{
		return *this = *this * b;
	}
	v2 &operator/=(T b)
	{
		return *this = *this / b;
	}
	friend T operator*(const v2 &a, const v2 &b)
	{
		return a.x * b.x + a.y * b.y;
	}
	friend T operator^(const v2 &a, const v2 &b)
	{
		return a.x * b.y - a.y * b.x;
	}
	friend T mag2(const v2 &a)
	{
		return a * a;
	}
	friend T mag(const v2 &a)
	{
		return sqrt(mag2(a));
	}
	friend v2 unit(const v2 &a)
	{
		return a / mag(a);
	}
	friend v2 r90(const v2 &a)
	{
		return {-a.y, a.x};
	}
	// vector projection onto a unit vector
	friend v2 uproj(const v2 &v, const v2 &u)
	{
		return (v * u) * u;
	}
	friend ostream &operator<<(ostream &os, const v2 &v)
	{
		return os << '(' << v.x << ',' << v.y << ')';
	}
};

struct tvec
{
	v2 p{}, v{};
	v2 operator()(T t) const
	{
		return p + v * t;
	}
	friend ostream &operator<<(ostream &os, const tvec &v)
	{
		return os << v.v << '_' << v.p;
	}
};

// Returns (s, t)
v2 isect(const tvec &a, const tvec &b)
{
	const auto [A, C] = a.v;
	const auto [B, D] = -b.v;
	const auto d	  = (a.p - b.p) / (a.v ^ b.v);
	return v2{v2{D, -B} * d, v2{-C, A} * d};
}

int	 n, m, k;
v2	 wh;
tvec gun;

struct seg
{
	tvec v;
	T	 l;
	int	 i;
	seg(v2 p1, v2 p2, int id) : v{p1, p2 - p1}, l(mag(v.v)), i(id)
	{
		v.v /= l;
	}
	friend ostream &operator<<(ostream &os, const seg &s)
	{
		return os << s.v(0) << " - " << s.v(s.l) << " (region " << s.i << ')';
	}
};

struct ray
{
	tvec v;
	T	 st;
	ray(tvec tv, T tim) : v(tv), st(tim) {}
	friend ostream &operator<<(ostream &os, const ray &ry)
	{
		return os << ry.v << " starting " << ry.v(ry.st);
	}
};

vector<seg> S;
vector<int> C;

vector<ray> R;

struct hit
{
	T	t;
	int ib, is;

	hit(T tim, int iball, int iseg) : t(tim), ib(iball), is(iseg) {}

	friend bool operator<(const hit &a, const hit &b)
	{
		if (a.t != b.t)
			return a.t < b.t;
		else
			return a.ib < b.ib;
	}

	ray nxt() const
	{
		const ray &r = R[ib];
		const seg &s = S[is];
		return ray{tvec{r.v.p + 2 * uproj(s.v.p - r.v.p, r90(s.v.v)), unit(2 * uproj(r.v.v, s.v.v) - r.v.v)}, t};
	}
};

vector<vector<hit>> H;

const auto o_cmp = [](int i, int j)
{
	return H[i].back() < H[j].back();
};

set<int, decltype(o_cmp)> O(o_cmp);

vector<priority_queue<T>> Q;

void cmp_hits(int ib)
{
	H[ib].clear();
	const ray &r = R[ib];
	for (int is = 0; is < k; is++)
	{
		const seg &s = S[is];
		if (abs(r.v.v ^ s.v.v) <= E)
			continue;
		auto [tr, ts] = isect(r.v, s.v);
		if (tr - r.st <= E || ts <= E || s.l - ts <= E)
			continue;
		H[ib].emplace_back(tr, ib, is);
	}
	sort(rbegin(H[ib]), rend(H[ib]));
}

void upd(int ib)
{
	const auto &hits = H[ib];
	const auto &ht	 = hits.back();
	int			is	 = ht.is;
	int			ir	 = S[is].i;
	int			c	 = C[ir];
	auto	   &que	 = Q[ir];
	que.push(ht.t);
	if ((int)que.size() > c)
		que.pop();
	O.insert(ib);
}

void proc()
{
	auto  it   = O.begin();
	auto &hits = H[*it];
	O.erase(it);
	const auto &ht	 = hits.back();
	auto [t, ib, is] = ht;
	int	  ir		 = S[is].i;
	auto &que		 = Q[ir];
	int	  c			 = C[ir];
	auto &ry		 = R[ib];

	if ((int)que.size() == c && que.top() - t <= DT)
		hits.pop_back();
	else
	{
		ry = ht.nxt();
		cmp_hits(ib);
	}
	if (is != 0)
		upd(ib);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> wh.x >> wh.y >> n >> m >> gun.p.x >> gun.v.x >> gun.v.y;
	m++;
	gun.v /= mag(gun.v);

	C.resize(m);

	C[0] = INT_MAX;
	S.emplace_back(v2{0, 0}, v2{wh.x, 0}, 0);
	S.emplace_back(v2{wh.x, 0}, wh, 0);
	S.emplace_back(wh, v2{0, wh.y}, 0);
	S.emplace_back(v2{0, wh.y}, v2{0, 0}, 0);

	{
		vector<v2> P;
		for (int i = 1; i < m; i++)
		{
			int p;
			cin >> p;
			P.resize(p);
			for (auto &[x, y] : P)
				cin >> x >> y;
			for (int j = 0; j < p; j++)
				S.emplace_back(P[j], P[(j + 1) % p], i);
			cin >> C[i];
		}
		k = (int)S.size();
	}

	R.reserve(n);
	H.resize(n);
	Q.resize(m);

	for (int i = 0; i < n; i++)
	{
		R.emplace_back(tvec{gun.p - i * gun.v, gun.v}, i);
		cmp_hits(i);
		upd(i);
	}

	while (!O.empty())
		proc();

	for (int i = 1; i < m; i++)
		cout << C[i] - Q[i].size() << ' ';
}
