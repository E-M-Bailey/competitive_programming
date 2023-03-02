#include <bits/stdc++.h>
using namespace std;
using T = __int128_t;
__int128_t gcd(__int128_t a, __int128_t b) { return b == 0 ? a : gcd(b, a % b); }
istream& operator>>(istream& is, __int128_t& x) { int64_t y; is >> y; x = y; return is; }
ostream& operator<<(ostream& os, const __int128_t& x) { return os << (int64_t)x; }
struct frac
{
	T n, d;
	void normalize()
	{
		if (d < 0) { n *= -1; d *= -1; }
		T g = gcd(n, d); n /= g; d /= g;
	}
	frac(T n = 0, T d = 1): n(n), d(d) { normalize(); }
	friend frac operator+(const frac& x) { return x; }
	friend frac operator-(const frac& x) { return { -x.n, x.d }; }
	friend frac operator+(const frac& x, const frac& y) { return { x.n * y.d + y.n * x.d, x.d * y.d }; }
	friend frac operator-(const frac& x, const frac& y) { return { x.n * y.d - y.n * x.d, x.d * y.d }; }
	friend frac operator*(const frac& x, const frac& y) { return { x.n * y.n, x.d * y.d }; }
	friend frac operator/(const frac& x, const frac& y) { return { x.n * y.d, x.d * y.n }; }
	friend bool operator<(const frac& x, const frac& y) { return x.n * y.d < y.n * x.d; }
	friend bool operator>(const frac& x, const frac& y) { return x.n * y.d > y.n * x.d; }
	friend bool operator<=(const frac& x, const frac& y) { return x.n * y.d <= y.n * x.d; }
	friend bool operator==(const frac& x, const frac& y) { return x.n * y.d == y.n * x.d; }
	friend bool operator!=(const frac& x, const frac& y) { return x.n * y.d != y.n * x.d; }
	friend T floor(const frac& x) { return x.n / x.d; }
	friend T ceil(const frac& x) { return (x.n + x.d - 1) / x.d; }
	friend ostream& operator<<(ostream& os, const frac& f) { return os << f.n << '/' << f.d; }
};
template<> struct std::hash<frac> { size_t operator()(const frac& f) const noexcept { return 129 * f.n + f.d; } };
template<class U, class T> struct std::hash<pair<U, T>> { size_t operator()(const pair<U, T>& f) const noexcept { return 31 * hash<U>()(f.first) + hash<T>()(f.second); } };
template<class T> T dot(const pair<T, T>& a, const pair<T, T>& b) { return a.first * b.first + a.second * b.second; }
template<class T> T cross(const pair<T, T>& a, const pair<T, T>& b) { return a.first * b.second - a.second * b.first; }
struct line
{
	T a, b, c;
	pair<frac, frac> ab() const { return { frac(a), frac(b) }; }
	pair<frac, frac> cb() const { return { frac(c), frac(b) }; }
	pair<frac, frac> ac() const { return { frac(a), frac(c) }; }
	friend bool operator<(const line& a, const line& b) { return 0 < cross(a.ab(), b.ab()); }
	friend pair<pair<frac, frac>, bool> isect(const line& a, const line& b)
	{
		frac d = cross(a.ab(), b.ab());
		return { d == 0 ? pair<frac, frac>{} : pair<frac, frac>{ cross(a.cb(), b.cb()) / d, cross(a.ac(), b.ac()) / d }, d != 0 };
	}
	bool under(const pair<frac, frac>& p) const { return dot(ab(), p) <= c; }
};
int main(int argc, const char* argv[])
{
	int t; cin >> t;
	while (t--)
	{
		int n; T tc, tm; cin >> n >> tc >> tm; n += 2;
		vector<line> L(n); L[0] = { 1, 0, tc }; L[1] = { 0, 1, tm };
		for (int i = 2; i < n; i++) cin >> L[i].a >> L[i].b >> L[i].c;
		unordered_set<pair<frac, frac>> IS;
		const auto put = [&](const line& a, const line& b)
		{
			auto [is, p] = isect(a, b);
			if (!p) return;
			if (is.first < 1 || is.second < 1) return;
			for (const line l : L) if (!l.under(is)) return;
			IS.insert(is);
		};
		line V{ -1, 0, -1 }, H{ 0, -1, -1 };
		for (int i = 0; i < n; i++)
		{
			put(V, L[i]); put(H, L[i]);
			for (int j = i + 1; j < n; j++) put(L[i], L[j]);
		}
		vector<pair<frac, frac>> ISS(begin(IS), end(IS));
		sort(begin(ISS), end(ISS), [](const pair<frac, frac>& a, pair<frac, frac>& b) { return a.first < b.first || (a.first == b.first && a.second > b.second); });
		for (int i = 0; i < size(ISS); i++)
			if (ISS[i].first == 1 && ISS[i].second == 1) swap(ISS[0], ISS[i]);
		T ans = 2;
		if (!ISS.empty())
		{
			for (auto it = next(begin(ISS)); it != end(ISS); it++)
			{
				auto [cx, cy] = *it; auto [px, py] = *prev(it);
				T xlo = ceil(px), xhi = floor(cx);
				if (xlo > xhi) continue;
				if (xlo == xhi && cx == px) { ans = max(ans, xlo + (T)floor(py)); continue; }
				frac m = (cy - py) / (cx - px);
				T ly = floor((xlo - px) * m + py);
				T ry = floor((xhi - px) * m + py);
				ans = max(ans, max(xlo + ly, xhi + ry));
			}
		}
		cout << tc + tm - ans << endl;
	}
}
/*
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, tc, tm;
		cin >> n >> tc >> tm;
		vector<vector<bool>> S(tc, vector<bool>(tm, true));
		for (int i = 0; i < n; i++) {
			int64_t a, b, c;
			cin >> a >> b >> c;
			for (int x = 1; x <= tc; x++)
				for (int y = 1; y <= tm; y++)
					S[x - 1][y - 1] = S[x - 1][y - 1] && a * x + b * y <= c;
		}
		int ans = INT_MAX;
		for (int i = 0; i < tc; i++) for (int j = 0; j < tm; j++) {
			if (S[i][j])
				ans = min(ans, tc - i + tm - j - 2);
		}
		cout << ans << endl;
	}
}*/