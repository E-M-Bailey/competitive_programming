#include <bits/extc++.h>

using namespace std;
namespace rng = ranges;

namespace
{
constexpr int sz(const auto& C) noexcept
{
	return static_cast<int>(size(C));
}

using ll = long long;

template<integral T>
struct bez
{
	using S = make_signed_t<T>;
	S x, y;
	T g;
	constexpr friend bez operator+(bez x, bez y) noexcept
	{
		return { x.x + y.x, x.y + y.y, x.g + y.g };
	}
	constexpr friend bez operator-(bez x, bez y) noexcept
	{
		return { x.x - y.x, x.y - y.y, x.g - y.g };
	}
	constexpr friend bez operator*(bez x, T y) noexcept
	{
		return { x.x * y, x.y * y, x.g * y };
	}
};
template<integral T>
constexpr bez<T> euclid(T a, T b) noexcept
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	if (a > b)
		swap(a, b);
	bez<T> A{ 1, 0, a }, B{ 0, 1, b };
	while (A.g != 0)
	{
		T q = B.g / A.g;
		A = exchange(B, A) - A * q;
	}
	return B;
}

constexpr int P = 1'000'000'007;

struct mint
{
	int n;
	explicit constexpr operator bool() noexcept
	{
		return n != 0;
	}
	friend constexpr bool operator!(mint x) noexcept
	{
		return x.n == 0;
	}
	friend constexpr mint operator-(mint x) noexcept
	{
		return { x ? P - x.n : 0 };
	}
	friend constexpr mint operator+(mint x, mint y) noexcept
	{
		return { x.n + y.n >= P ? x.n + y.n - P : x.n + y.n };
	}
	friend constexpr mint operator-(mint x, mint y) noexcept
	{
		return x + -y;
	}
	friend constexpr mint operator*(mint x, mint y) noexcept
	{
		return { static_cast<int>(static_cast<ll>(x.n) * y.n % P) };
	}
	friend constexpr mint inv(mint x) noexcept
	{
		auto B = euclid(x.n, P);
		B.x %= P;
		return { B.x < 0 ? B.x + P : B.x };
	}
	friend constexpr mint operator/(mint x, mint y) noexcept
	{
		return x * inv(y);
	}
	friend inline ostream &operator<<(ostream &os, mint x) noexcept
	{
		return os << x.n;
	}
};
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		mint x;
		cin >> n >> x.n;

		vector<mint> A, M;
		string s;
		while (n--)
		{
			cin >> s;
			mint y{ stoi(s.substr(1)) };
			if (s[0] == '+')
				A.push_back(y);
			else if (s[0] == '-')
				A.push_back(-y);
			else if (s[0] == 'x')
				M.push_back(y);
			else
				M.push_back(inv(y));
		}
		int nm = sz(M);

		vector<mint> DP(nm + 1);
		DP[0] = { 1 };
		for (int i = 1; i <= nm; ++i)
			for (int j = i; j--;)
				DP[j + 1] = DP[j + 1] + DP[j] * M[i - 1];
		mint em{}, c = inv(mint{ nm + 1 });
		for (int i = 0; i <= nm; ++i)
		{
			em = em + DP[i] * c;
			c = c * mint{ i + 1 } / mint{ nm - i };
		}
		mint e = rng::fold_left(M, x, multiplies{}) + em * *rng::fold_left_first(A, plus{});
		cout << e.n << '\n';
	}
}
