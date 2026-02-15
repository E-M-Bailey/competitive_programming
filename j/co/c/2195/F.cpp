#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

using ll = long long;

struct par
{
	int a, b, c;
	constexpr ll discr() const
	{
		return (ll)b * b - 4ll * a * c;
	}
	constexpr bool has_root() const
	{
		return a == 0 ? b != 0 || c == 0 : discr() >= 0;
	}
	constexpr friend par operator-(par f, par g)
	{
		return { f.a - g.a, f.b - g.b, f.c - g.c };
	}
	constexpr friend bool operator<(par f, par g)
	{
		return f.c < g.c && !(f - g).has_root();
	};
	friend istream &operator>>(istream &is, par &f)
	{
		return is >> f.a >> f.b >> f.c;
	}
};
struct ipar : par
{
	int i;
};

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		vector<ipar> P(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> P[i];
			P[i].i = i;
		}
		rng::sort(P, {}, &ipar::c);
		vector<int> R(n);

		vector<int> D(n), U(n);
		for (int i = n - 1; i >= 0; --i)
			for (int j = i + 1; j < n; ++j)
				if (P[i] < P[j])
					U[i] = max(U[i], 1 + U[j]);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < i; ++j)
				if (P[j] < P[i])
					D[i] = max(D[i], 1 + D[j]);
			R[P[i].i] = D[i] + U[i] + 1;
		}
		for (int i = 0; i < n; ++i)
			cout << R[i] << ' ';
		cout << '\n';
	}
}
