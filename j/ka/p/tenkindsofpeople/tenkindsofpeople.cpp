#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;
namespace rng = ranges;
namespace vws = views;

using u64 = uint64_t;
using d_t = array<int, 128>;
using a_t = array<u64, 5>;

template<typename T>
static inline T input(istream &is = cin)
{
	static T x;
	is >> x;
	return x;
}

static constexpr d_t D = []()
{
	d_t D{};
	for (int c = '0'; c <= '9'; ++c)
		D[c] = c - '0';
	for (int c = 'a'; c <= 'z'; ++c)
		D[c] = c - 'a' + 10;
	for (int c = 'A'; c <= 'Z'; ++c)
		D[c] = c - 'A' + 36;
	return D;
}();
static constexpr auto d_at = bind(static_cast<int const &(d_t::*)(size_t) const>(&d_t::operator[]), D, _1);

static inline auto nxt()
{
	a_t A{};
	rng::copy(input<string>() | vws::reverse | vws::transform(d_at), begin(A));
	return pair<a_t, u64>{ A, max<u64>(2, rng::max(A) + 1) };
}

static inline u64 eval(a_t const &A, u64 b)
{
	return rng::fold_right(A, u64{}, [b](u64 l, u64 r) { return l + r * b; });
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		auto const [A, la] = nxt();
		auto const [B, lb] = nxt();

		bool done = false;
		for (u64 ba = la, bb = lb, va = eval(A, ba), vb = eval(B, bb); !done && ba <= 7500 && bb <= 7500;)
		{
			if (va < vb)
				va = eval(A, ++ba);
			else if (va > vb)
				vb = eval(B, ++bb);
			else
			{
				cout << va << ' ' << ba << ' ' << bb << '\n';
				done = true;
			}
		}
		if (!done)
			cout << "CANNOT MAKE EQUAL\n";
	}
}
