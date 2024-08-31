#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll constexpr M = 1000000007;

// Source: KACTL
struct Tree
{
	typedef array<int, 101> T;
	static constexpr T		unit{1};
	T						f(T a, T b)
	{
		T ans{};
		for (int i = 0; i <= 100; i++)
			for (int j = 0; i + j <= 100; j++)
				ans[i + j] = int((ans[i + j] + (ll)a[i] * b[j]) % M);
		return ans;
	}
	vector<T> s;
	int		  n;
	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	void init(vector<int> const &A, int l, int r, int pos)
	{
		T &S = s[pos];
		for (int i = l; i < r; i++)
			for (int j = 100; j > 0; j--)
				S[j] = (S[j] + (ll)S[j - 1] * A[i]) % M;
		if (l + 1 < r)
		{
			int m = (l + r) / 2;
			init(A, l, m, pos * 2);
			init(A, m, r, pos * 2 + 1);
		}
	}
	void init(vector<int> const &A)
	{
		init(A, 0, (int)size(s) / 2, 1);
	}
	T query(int b, int e)
	{ // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2)
		{
			if (b % 2)
				ra = f(ra, s[b++]);
			if (e % 2)
				rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

Tree::T sing(int x)
{
	Tree::T ans = Tree::unit;
	ans[1]		= int(x % M);
	return ans;
}

int main()
{
	int n, c, t;
	cin >> n >> c >> t;
	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N++;

	vector<int> A(N);
	for (int i = 0; i < n; i++)
	{
		int l, r;
		cin >> l >> r;
		A[i] = r - l + 1;
	}

	Tree T(N);
	T.init(A);

	while (t--){
		int c, x, y, z;
		cin >> c >> x >> y >> z;
		if (c == 0)
		{
			x--;
			y--;
			auto ans = T.query(x, y + 1);
			cout << ans[z] << '\n';
		}
		else if (c == 1)
		{
			x--;
			T.update(x, sing(z - y + 1));
		}
	}
}
