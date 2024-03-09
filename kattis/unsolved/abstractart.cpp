#include <bits/stdc++.h>

using namespace std;

constexpr long double EPS = 1e-11l;

template<typename T>
struct vec2
{
	T x, y;
};
template<typename T>
static constexpr vec2<T> operator+(vec2<T> a) noexcept
{
	return {+a.x, +a.y};
}
template<typename T>
static constexpr vec2<T> operator-(vec2<T> a) noexcept
{
	return {-a.x, -a.y};
}
template<typename T>
static constexpr vec2<T> operator+(vec2<T> a, vec2<T> b) noexcept
{
	return {a.x + b.x, a.y + b.y};
}
template<typename T>
static constexpr vec2<T> operator-(vec2<T> a, vec2<T> b) noexcept
{
	return {a.x - b.x, a.y - b.y};
}
template<typename T>
static constexpr vec2<T> operator*(vec2<T> a, T b) noexcept
{
	return {a.x * b, a.y * b};
}
template<typename T>
static constexpr vec2<T> operator*(T a, vec2<T> b) noexcept
{
	return {a * b.x, a * b.y};
}
template<typename T>
static constexpr vec2<T> operator/(vec2<T> a, T b) noexcept
{
	return {a.x / b, a.y / b};
}
template<typename T>
static constexpr T operator*(vec2<T> a, vec2<T> b) noexcept
{
	return a.x * b.x + a.y * b.y;
}
template<typename T>
static constexpr T operator^(vec2<T> a, vec2<T> b) noexcept
{
	return a.x * b.y - a.y * b.x;
}
template<typename T>
static constexpr bool operator==(vec2<T> a, vec2<T> b) noexcept
{
	return a.x == b.x && a.y == b.y;
}
template<typename T>
static constexpr bool operator<(vec2<T> a, vec2<T> b) noexcept
{
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
template<typename T>
static istream &operator>>(istream &is, vec2<T> &v)
{
	return is >> v.x >> v.y;
}

template<typename T>
struct mat2
{
	vec2<T> a, b;

	constexpr vec2<T> operator()(vec2<T> x) noexcept
	{
		return {a * x, b * x};
	}
};

template<typename T>
static constexpr mat2<T> operator+(mat2<T> a) noexcept
{
	return {+a.a, +a.b};
}
template<typename T>
static constexpr mat2<T> operator-(mat2<T> a) noexcept
{
	return {-a.a, -a.b};
}
template<typename T>
static constexpr mat2<T> tpose(mat2<T> a) noexcept
{
	return {{a.a.x, a.b.x}, {a.a.y, a.b.y}};
}
template<typename T>
static constexpr T det(mat2<T> a) noexcept
{
	return a.a ^ a.b;
}
template<typename T>
static constexpr mat2<T> operator+(mat2<T> a, mat2<T> b) noexcept
{
	return {a.a + b.a, a.b + b.b};
}
template<typename T>
static constexpr mat2<T> operator-(mat2<T> a, mat2<T> b) noexcept
{
	return {a.a - b.a, a.b - b.b};
}
template<typename T>
static constexpr mat2<T> operator*(mat2<T> a, T b) noexcept
{
	return {a.a * b, a.b * b};
}
template<typename T>
static constexpr mat2<T> operator*(T a, mat2<T> b) noexcept
{
	return {a * b.a, a * b.b};
}
template<typename T>
static constexpr vec2<T> operator*(mat2<T> a, vec2<T> b) noexcept
{
	return {a.a * b, a.b * b};
}
template<typename T>
static constexpr vec2<T> operator*(vec2<T> a, mat2<T> b) noexcept
{
	return a.x * b.a + a.y * b.b;
}
template<typename T>
static constexpr mat2<T> operator*(mat2<T> a, mat2<T> b) noexcept
{
	return {a.a * b, a.b * b};
}
template<typename T>
static constexpr mat2<T> operator/(mat2<T> a, T b) noexcept
{
	return {a.a / b, a.b / b};
}
template<typename T>
static constexpr mat2<T> inv(mat2<T> a) noexcept
{
	return mat2<T>{{a.b.y, -a.a.y}, {-a.b.x, a.a.x}} / det(a);
}

template<typename T>
struct seg2;

template<typename T>
constexpr vec2<T> del(seg2<T> s) noexcept;
template<typename T>
constexpr vec2<T> is_right(seg2<T> s) noexcept;

template<typename T>
struct seg2
{
	vec2<T> a, b;

	constexpr vec2<T> operator()(T t) const noexcept
	{
		return a + t * del(*this);
	}

	constexpr T y_at(vec2<T> x) const noexcept
	{
		T t = (x - a.x) / del().x;
		return (1 - t) * a.y + t * b.y;
	}

	constexpr bool is_above(vec2<T> p) const noexcept
	{
		if (p.x < min(a.x, b.x) || p.x >= max(a.x, b.x))
			return false;
		return y_at(p.x) > p.y;
	}
};

template<typename T>
static constexpr vec2<T> del(seg2<T> s) noexcept
{
	return s.b - s.a;
}
template<typename T>
static constexpr bool is_right(seg2<T> s) noexcept
{
	return s.del().x > 0;
}
template<typename T>
static constexpr seg2<T> rev(seg2<T> s) noexcept
{
	return {s.b, s.a};
}

template<typename T, typename Cmp>
struct y_cmp
{
	T		 &tim;
	Cmp const cmp;

	constexpr bool operator()(seg2 a, seg2 b) const noexcept
	{
		return cmp(a.y_at(tim), b.y_at(tim));
	}
};

// v1 t + q1 = v2 u + q2
// v1 t - v2 u = q2 - q1
// [vx1 -vx2] [t] = [qx2 - qx1]
// [vy1 -vy2] [u]   [qy2 - qy1]

// Returns coefficients
template<typename T>
static constexpr vec2<T> isect(seg2<T> a, seg2<T> b) noexcept
{
	mat2 A = tpose({a.b - a.a, b.a - b.b});
	if (abs(det(A)) >= EPS)
	{
		vec2<T> B	= b.a - a.a;
		vec2<T> ans = inv(A) * B;
		if (-EPS <= ans.x && ans.x <= 1 + EPS && -EPS <= ans.y && ans.y <= 1 + EPS)
			return ans;
	}
	return {-1, -1};
}

template<typename T>
struct pgon
{
	int				n = 0;
	vector<vec2<T>> P{};

	constexpr bool contains(vec2 p) const noexcept
	{
		bool ans = false;
		for (int i = 0; i < n; i++)
			ans ^= seg2<T>{P[i], P[i + 1]}.is_above(p);
		return ans;
	}

	// Signed area (positive <=> ccw)
	constexpr T area() const noexcept
	{
		T ans = 0;
		for (int i = 0; i < n; i++)
			ans += P[i] ^ P[i + 1];
		return ans / 2;
	}

	constexpr operator bool() const noexcept
	{
		return n != 0;
	}

	constexpr void transform(mat2<T> tr) noexcept
	{
		for (auto &p : P)
			p = tr * p;
	}
};

/*
// Modified Greiner–Hormann Clipping Algorithm
static pgon onion(pgon const &a, pgon const &b) noexcept
{
	int n = a.n, m = b.n;

	vector<vector<tuple<T, bool, int, int, int>>> A(n), B(m);

	bool has_isect = false;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			seg2 sa{a.P[i], a.P[i + 1]}, sb{b.P[j], b.P[j + 1]};
			auto [s, t] = isect(sa, sb);
			if (s >= 0)
			{
				has_isect = true;
				A[i].emplace_back(s, 0, j, (int)size(B[j]), (int)size(A[i]));
				B[j].emplace_back(t, 0, i, (int)size(A[i]) - 1, (int)size(B[j]));
			}
		}

	if (!has_isect)
	{
		if (a.contains(b.P[0]))
			return a;
		else if (b.contains(a.P[0]))
			return b;
		else
			return {};
	}

	for (auto &AA : A)
		sort(begin(AA), end(AA));
	for (auto &BB : B)
		sort(begin(BB), end(BB));

	vector<vector<int>> PA(n), PB(m);
	for (int i = 0; i < n; i++)
	{
		PA[i].resize(size(A[i]));
		for (int j = 0; j < (int)size(A[i]); j++)
			PA[i][get<4>(A[i][j])] = j;
	}
	for (int i = 0; i < m; i++)
	{
		PB[i].resize(size(B[i]));
		for (int j = 0; j < (int)size(B[i]); j++)
			PB[i][get<4>(B[i][j])] = j;
	}

	pgon c;

	bool p;
	int	 i = -1, j = -1;

	{
		bool ct = b.contains(a.P[0]);
		for (int k = 0; k < n; k++)
		{
			if (i < 0 && !ct)
				i = k;
			for (auto &[t, in, ii, jj, id] : A[k])
				in = ct = !ct;
		}
		p  = i < 0;
		ct = a.contains(b.P[0]);
		for (int k = 0; k < m; k++)
		{
			if (i < 0 && !ct)
				i = k;
			for (auto &[t, in, ii, jj, id] : B[k])
				in = ct = !ct;
		}
	}

	bool sp = p;
	int	 si = i, sj = j;
	do
	{
		if (j < 0)
			c.P.push_back((p ? b : a).P[i]);
		else
		{
			auto [t, in, ii, jj, id] = (p ? B : A)[i][j];
			c.P.push_back(seg2{(p ? b : a).P[i], (p ? b : a).P[i + 1]}(t));
			if (in)
			{
				p = !p;
				i = ii;
				j = (p ? PB : PA)[i][jj];
			}
		}

		if (++j == (int)size((p ? B : A)[i]))
		{
			j = -1;
			if (++i == (p ? b : a).n)
				i = 0;
		}
	}
	while (p != sp || i != si || j != sj);

	c.n = (int)size(c.P);
	c.P.push_back(c.P.front());
	return c;
}
*/

template<typename T>
static istream &operator>>(istream &is, pgon<T> &p)
{
	is >> p.n;
	p.P.reserve(p.n + 1);
	p.P.resize(p.n);
	for (auto &pt : p.P)
		is >> pt;
	p.P.push_back(p.P[0]);
	p.P.push_back(p.P[1]);
	if (p.area() < 0)
		reverse(begin(p.P), end(p.P));
	return is;
}

typedef long double T;

struct event
{
	vec2<T> pos;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(7);

	int n;
	cin >> n;
	vector<pgon<T>> P(n);

	T paint = 0;

	for (auto &p : P)
	{
		cin >> p;
		// prevent vertical line segments and events with the same x-coordinate
		p.transform({{1, EPS}, {0, 1}});
		paint += p.area();

		for (int i = 0; i < p.n; i++)
		{
			
		}
	}

	T tim = 0;

	T canvas = 0;

	cout << paint << ' ' << canvas;
}
