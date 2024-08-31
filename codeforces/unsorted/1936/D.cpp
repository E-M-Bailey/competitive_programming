#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

int v;

struct ent
{
	int mx = 0, bor = 0, sub = INT_MAX;
	// vector<pair<int, int>> P{}, S{};
	array<pair<int, int>, 30> P{}, S{};
	int						  p = 0, s = 0;

	ent() = default;
	ent(int a, int b) : mx(a), bor(b), sub(b >= v ? a : INT_MAX)
	{
		if (b > 0)
		{
			P[p++] = {b, a};
			S[s++] = {b, a};
		}
	}
};

ent operator+(ent const &A, ent const &B)
{
	ent C;
	C.mx  = max(A.mx, B.mx);
	C.bor = A.bor | B.bor;
	C.sub = min(A.sub, B.sub);

	copy(begin(A.P), begin(A.P) + A.p, begin(C.P));
	C.p = A.p;
	for (int i = 0; i < B.p; i++)
	{
		auto [b, a] = B.P[i];
		b |= A.bor;
		a = max(a, A.mx);
		if (C.p == 0 || b > C.P[C.p - 1].first)
			C.P[C.p++] = {b, a};
	}
	copy(begin(B.S), begin(B.S) + B.s, begin(C.S));
	C.s = B.s;
	for (int i = 0; i < A.s; i++)
	{
		auto [b, a] = A.S[i];
		b |= B.bor;
		a = max(a, B.mx);
		if (C.s == 0 || b > C.S[C.s - 1].first)
			C.S[C.s++] = {b, a};
	}

	for (int l = A.s, r = 0; l-- > 0;)
	{
		while (r < B.p && (A.S[l].first | B.P[r].first) < v)
			r++;
		if (r == B.p)
			break;
		C.sub = min(C.sub, max(A.S[l].second, B.P[r].second));
	}

	return C;
}

struct tree
{
	typedef ent	   T;
	static T const unit;

	T f(T const &a, T const &b)
	{
		return a + b;
	}
	vector<T> s;
	int		  n;
	tree(int N = 0, T def = unit) : s(2 * N, def), n(N) {}
	void update(int pos, T const &val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e)
	{
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
tree::T const tree::unit{};

void go()
{
	int n;
	cin >> n >> v;

	vector<int> A(n), B(n);
	for (int &a : A)
		cin >> a;
	for (int &b : B)
		cin >> b;

	tree T(n);
	for (int i = 0; i < n; i++)
		T.update(i, {A[i], B[i]});

	int q;
	cin >> q;
	while (q--)
	{
		int c, x, y;
		cin >> c >> x >> y;
		x--;
		if (c == 1)
		{
			B[x] = y;
			T.update(x, {A[x], y});
		}
		else
		{
			auto Q = T.query(x, y);
			cout << (Q.sub == INT_MAX ? -1 : Q.sub) << ' ';
		}
	}
	cout << '\n';
}
