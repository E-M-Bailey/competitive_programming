#include <bits/stdc++.h>

using namespace std;

typedef long long		   ll;
typedef unsigned long long ull;

constexpr ull M = 1e11 + 3, P = M - 1;

struct mint
{
	ull x;
	mint(int X) : x((X % (ll)M + M) % M) {}
	mint(ull X = 0) : x(X % M) {}
	friend mint operator-(mint a)
	{
		return {M - a.x};
	}
	friend mint operator+(mint a, mint b)
	{
		return {a.x + b.x};
	}
	mint &operator+=(mint b)
	{
		return *this = *this + b;
	}
	friend mint operator-(mint a, mint b)
	{
		return {M + a.x - b.x};
	}
	mint &operator-=(mint b)
	{
		return *this = *this - b;
	}
	friend mint operator*(mint a, mint b)
	{
		ll ret = a.x * b.x - M * ull(1.l / M * a.x * b.x);
		return ret + M * (ret < 0) - M * (ret >= (ll)M);
	}
	mint &operator*=(mint b)
	{
		return *this = *this * b;
	}
	friend mint mpow(mint a, ll b)
	{
		mint ans = 1;
		for (b = (b % (ll)P + P) % P; b; b /= 2, a *= a)
			if (b % 2)
				ans *= a;
		return ans;
	}
	friend mint minv(mint a)
	{
		return mpow(a, -1);
	}
	friend mint operator/(mint a, mint b)
	{
		return a * minv(b);
	}
	mint &operator/=(mint b)
	{
		return *this = *this / b;
	}
	friend ostream &operator<<(ostream &os, mint a)
	{
		return os << a.x;
	}
};

constexpr int N = 5;

struct poly
{
	array<mint, N> A{};
	template<class... Args>
	explicit poly(Args &&...args) : A{forward<Args>(args)...}
	{}
	mint &operator[](int i)
	{
		return A[i];
	}
	mint operator[](int i) const
	{
		return A[i];
	}
	friend poly operator-(const poly &f)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			h[i] = -f[i];
		return h;
	}
	friend poly operator+(const poly &f, const poly &g)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			h[i] = f[i] + g[i];
		return h;
	}
	friend poly operator+(const poly &f, mint b)
	{
		poly h = f;
		h[0] += b;
		return h;
	}
	friend poly operator+(mint a, const poly &g)
	{
		poly h = g;
		h[0] += a;
		return h;
	}
	poly &operator+=(const poly &g)
	{
		return *this = *this + g;
	}
	poly &operator+=(mint b)
	{
		return *this = *this + b;
	}
	friend poly operator-(const poly &f, const poly &g)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			h[i] = f[i] - g[i];
		return h;
	}
	friend poly operator-(const poly &f, mint b)
	{
		poly h = f;
		h[0] -= b;
		return h;
	}
	friend poly operator-(mint a, const poly &g)
	{
		poly h = -g;
		h[0] += a;
		return h;
	}
	poly &operator-=(const poly &g)
	{
		return *this = *this - g;
	}
	poly &operator-=(mint b)
	{
		return *this = *this - b;
	}
	friend poly operator*(const poly &f, const poly &g)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			for (int j = 0; i + j < N; j++)
				h[i + j] += f[i] * g[j];
		return h;
	}
	friend poly operator*(const poly &f, mint b)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			h[i] = f[i] * b;
		return h;
	}
	friend poly operator*(mint a, const poly &g)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			h[i] = a * g[i];
		return h;
	}
	poly &operator*=(const poly &g)
	{
		return *this = *this * g;
	}
	poly &operator*=(mint b)
	{
		return *this = *this * b;
	}
	friend poly operator/(const poly &f, mint b)
	{
		poly h{};
		for (int i = 0; i < N; i++)
			h[i] = f[i] / b;
		return h;
	}
	poly &operator/=(mint b)
	{
		return *this = *this / b;
	}
	friend poly ppow(poly f, ull b)
	{
		poly h{1};
		while (b--)
			h *= f;
		return h;
	}
	friend poly psum(const poly &f)
	{
		return poly{
			0, f[0] + (3 * f[1] + f[2]) / 6, (2 * (f[1] + f[2]) + f[3]) / 4, (2 * f[2] + 3 * f[3]) / 6, f[3] / 4};
	}
	poly operator()(const poly &g) const
	{
		poly h{};
		for (int i = N - 1; i >= 0; i--)
			h = h * g + A[i];
		return h;
	}
	mint operator()(mint x) const
	{
		mint y = 0;
		for (int i = N - 1; i >= 0; i--)
			y = y * x + A[i];
		return y;
	}
	mint operator()(mint a, mint b) const
	{
		return (*this)(b) - (*this)(a);
	}

	friend ostream &operator<<(ostream &os, const poly &f)
	{
		os << '<';
		for (int i = 0; i < N; i++)
			os << ' ' << f[i];
		return os << " >";
	}
};

int main()
{
	ull r, c, k;
	cin >> r >> c >> k;
	if (r < c)
		swap(r, c);

	mint R = r, C = c, K = k;
	mint A = k > c ? k - c : 0;
	mint B = k > r ? k - r : 0;
	mint D = k > c + r - 1 ? k - (c + r - 1) : 0;

	mint S = ((K + 1) * (K + 1) + K * K) * R * C;

	poly Km{K, -1};

	poly P1 = psum((Km * Km)(Km));
	mint Sh = R * P1(A, K);
	mint Sv = C * P1(B, K);

	poly P2	 = Km * (Km - 1) / 2;
	poly P2a = psum((poly{1, 1} * P2)(Km)), P2b = psum((C * P2)(Km)), P2c = psum((poly{C + R - 1, -1} * P2)(Km));
	mint Shv = P2a(A, K);
	if (k > c)
		Shv += P2b(B, K - C);
	if (k > r)
		Shv += P2c(D, K - R);

	cout << 1 - (S - 2 * (Sh + Sv) + 4 * Shv) / (R * R * C * C);
}
