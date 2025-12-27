#include <cstring>
#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef _MSC_VER
inline int __builtin_clz(unsigned int value)
{
	return __lzcnt(value);
}
inline int __builtin_clzl(unsigned long int value)
{
	return __lzcnt(value);
}
inline int __builtin_clzll(unsigned long long int value)
{
	return value & 0xffffffff00000000ull ? __lzcnt(value >> 32) : 32 + __lzcnt(value);
}
inline constexpr int __builtin_ctzll(unsigned long long int value);
inline constexpr int __builtin_ctz(unsigned int value)
{
	return __builtin_ctzll(value);
}
inline constexpr int __builtin_ctzl(unsigned long int value)
{
	return __builtin_ctzll(value);
}
inline constexpr int __builtin_ctzll(unsigned long long int value)
{
	if (value == 0)
	{
		return 437; // undefined
	}
	int ctr = 0;
#define CTZ_SEGMENT(n) do { if (!(value & ((1ull << (n)) - 1))) { ctr |= (n); value >>= (n); } } while (0)
	CTZ_SEGMENT(1 << 5);
	CTZ_SEGMENT(1 << 4);
	CTZ_SEGMENT(1 << 3);
	CTZ_SEGMENT(1 << 2);
	CTZ_SEGMENT(1 << 1);
	CTZ_SEGMENT(1 << 0);
#undef CTZ_SEGMENT
	return ctr;
}
#endif

#define loop(m, n, i) for (ui i = (m); i < (n); i++)
#define rloop(m, n, i) for (ui i = (n); i-- > (m);)
#define loop_each(vec, i, x) auto x = vec.front(); for (ui i = 0; i < (vec).size(); i++, x = vec[i])
#define rloop_each(vec, i, x) auto x = vec.back(); for (ui i = (vec).size(); i-- > 0; x = vec[i - 1])

#define tCases() ui testCaseCount; cin >> testCaseCount; for (ui testCaseIndex = 0; testCaseIndex < testCaseCount; testCaseIndex++)

#define endl '\n'

using namespace std;

template<class T>
struct frac;

typedef bool                 bi;
typedef char                 ci;
typedef unsigned char        uci;
typedef frac<ci>             fci;
typedef frac<uci>            fuci;
typedef short                si;
typedef unsigned short       usi;
typedef frac<si>             fsi;
typedef frac<usi>            fusi;
typedef int                  li;
typedef unsigned             uli;
typedef frac<li>             fli;
typedef frac<uli>            fuli;
typedef long long            lli;
typedef unsigned long long   ulli;
typedef frac<lli>            flli;
typedef frac<ulli>           fulli;
typedef float                sf;
typedef double               df;
typedef long double          ldf;

typedef pair<bi, bi>         pbi;
typedef pair<ci, ci>         pci;
typedef pair<uci, uci>       puci;
typedef pair<fci, fci>       pfci;
typedef pair<fuci, fuci>     pfuci;
typedef pair<si, si>         psi;
typedef pair<usi, usi>       pusi;
typedef pair<fsi, fsi>       pfsi;
typedef pair<fusi, fusi>     pfusi;
typedef pair<li, li>         pli;
typedef pair<uli, uli>       puli;
typedef pair<fli, fli>       pfli;
typedef pair<fuli, fuli>     pfuli;
typedef pair<lli, lli>       plli;
typedef pair<ulli, ulli>     pulli;
typedef pair<flli, flli>     pflli;
typedef pair<fulli, fulli>   pfulli;
typedef pair<sf, sf>         psf;
typedef pair<df, df>         pdf;
typedef pair<ldf, ldf>       pldf;

typedef vector<bi>           vbi;
typedef vector<ci>           vci;
typedef vector<uci>          vuci;
typedef vector<fci>          vfci;
typedef vector<fuci>         vfuci;
typedef vector<si>           vsi;
typedef vector<usi>          vusi;
typedef vector<fsi>          vfsi;
typedef vector<fusi>         vfusi;
typedef vector<li>           vli;
typedef vector<uli>          vuli;
typedef vector<fli>          vfli;
typedef vector<fuli>         vfuli;
typedef vector<lli>          vlli;
typedef vector<ulli>         vulli;
typedef vector<flli>         vflli;
typedef vector<fulli>        vfulli;
typedef vector<sf>           vsf;
typedef vector<df>           vdf;
typedef vector<ldf>          vldf;

typedef vector<pbi>          vpbi;
typedef vector<pci>          vpci;
typedef vector<puci>         vpuci;
typedef vector<pfci>         vpfci;
typedef vector<pfuci>        vpfuci;
typedef vector<psi>          vpsi;
typedef vector<pusi>         vpusi;
typedef vector<pfsi>         vpfsi;
typedef vector<pfusi>        vpfusi;
typedef vector<pli>          vpli;
typedef vector<puli>         vpuli;
typedef vector<pfli>         vpfli;
typedef vector<pfuli>        vpfuli;
typedef vector<plli>         vplli;
typedef vector<pulli>        vpulli;
typedef vector<pflli>        vpflli;
typedef vector<pfulli>       vpfulli;
typedef vector<psf>          vpsf;
typedef vector<pdf>          vpdf;
typedef vector<pldf>         vpldf;

#define MIN(T) (numeric_limits<T>::min())
#define MAX(T) (numeric_limits<T>::max())

inline constexpr uli gcd(uli l, uli r)
{
	if (!(l && r))
	{
		return l | r;
	}
	int s = __builtin_ctz(l | r);
	l >>= __builtin_ctz(l);
	do
	{
		r >>= __builtin_ctz(r);
		if (l > r)
		{
			swap(l, r);
		}
		r -= l;
	}
	while (r);
	return l << s;
}

inline constexpr ulli gcd(ulli l, ulli r)
{
	if (!(l && r))
	{
		return l | r;
	}
	int s = __builtin_ctzll(l | r);
	l >>= __builtin_ctzll(l);
	do
	{
		r >>= __builtin_ctzll(r);
		if (l > r)
		{
			swap(l, r);
		}
		r -= l;
	}
	while (r);
	return l << s;
}

template<class T>
struct frac
{
	using N = T;
	using D = make_unsigned_t<T>;

	N n;
	D d;

	inline constexpr frac r() const
	{
		D g = gcd(abs(n), d);
		return { n / g, d / g };
	}

	inline constexpr frac i() const
	{
		return n < 0 ? frac{ -(N)d, (D)-n } : frac{ (N)d, (D)n };
	}

	inline constexpr frac operator+() const
	{
		return { n, d };
	}

	inline constexpr frac operator-() const
	{
		return { -n, d };
	}

	inline constexpr frac operator+(const frac& f) const
	{
		return { n * (N)f.d + f.n * (N)d, d * f.d };
	}

	inline constexpr frac operator-(const frac& f) const
	{
		return { n * (N)f.d - f.n * (N)d, d * f.d };
	}

	inline constexpr frac operator*(const frac& f) const
	{
		return { n * f.n, d * f.d };
	}

	inline constexpr frac operator/(const frac& r) const
	{
		return n < 0 ? frac{ n * -(N)r.d, d * (D)-r.n } : frac{ n * (N)r.d, d * (D)r.n };
	}

	template<class S>
	inline constexpr frac operator<<(const S& s)
	{
		return { n << s, d };
	}

	template<class S>
	inline constexpr frac operator>>(const S& s)
	{
		return { n, d << s };
	}

	inline constexpr bool operator==(const frac& f)
	{
		return n * f.d == f.n * d;
	}

	inline constexpr bool operator!=(const frac& f)
	{
		return n * f.d != f.n * d;
	}

	inline constexpr bool operator<(const frac& f)
	{
		return n * f.d < f.n * d;
	}

	inline constexpr bool operator<=(const frac& f)
	{
		return n * f.d <= f.n * d;
	}

	inline constexpr bool operator>(const frac& f)
	{
		return n * f.d > f.n * d;
	}

	inline constexpr bool operator>=(const frac& f)
	{
		return n * f.d >= f.n * d;
	}

	inline constexpr operator bool() const
	{
		return d;
	}

	template<class S>
	inline constexpr explicit operator frac<S>() const
	{
		return frac<S>{ (typename frac<S>::N)n, (typename frac<S>::D)(d) };
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ulli a, b;
	while (cin >> a >> b)
	{
		cout << (a > b ? a - b : b - a) << endl;
		cout.flush();
	}

	return 0;
}