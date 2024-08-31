#include <bits/stdc++.h>

using namespace std;

// Source: KACTL
struct mTree
{
	typedef int		   T;
	static constexpr T unit = INT_MAX;
	T				   f(T a, T b)
	{
		return min(a, b);
	} // (any associative fn)
	vector<T> s;
	int		  n;
	mTree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
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
struct MTree
{
	typedef int		   T;
	static constexpr T unit = INT_MIN;
	T				   f(T a, T b)
	{
		return max(a, b);
	} // (any associative fn)
	vector<T> s;
	int		  n;
	MTree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
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

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> I(n);
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		a--;
		I[a].push_back(i);
	}

	mTree mT(n);
	MTree MT(n);
	int	  A = -1;
	for (int a = n; a-- > 0;)
	{
		for (int j = 1; A < 0 && j < (int)size(I[a]); j++)
		{
			int l = I[a][j - 1], r = I[a][j];
			if (mT.query(l, r) < l || MT.query(l, r) > r)
			{
				A = a;
				break;
			}
		}
		if (A < 0)
			break;
		for (int j = 1; j < (int)size(I[a]); j++)
		{
			int l = I[a][j - 1], r = I[a][j];
			mT.update(r, l);
			MT.update(l, r);
		}
	}
	cout << A;
	if (A < 0)
		return;

	/*
	map<int, pair<int, int>> M;
	auto const				 fnd = [&](int i)
	{
		auto it = M.upper_bound(i);
		if (it == end(M) || it->second.first > i)
			return -1;
		return it->second.second;
	};
	int			A = INT_MAX, B = INT_MAX;
	vector<int> C;
	for (int a = 0; a < n; a++)
	{
		if ((int)size(I[a]) < 2)
			continue;
		for (int j = 1; j < (int)size(I[a]); j++)
		{
			int l = I[a][j - 1], r = I[a][j];
			int x = fnd(l), y = fnd(r);
			if (x != y)
			{
				if (x >= 0)
					tie(A, B) = min(pair{A, B}, pair{C[x], a});
			}
			if (A == INT_MAX)
			{
				M.emplace(r, pair{l, (int)size(C)});
				C.push_back(a);
			}
		}
	}
	if (A == INT_MAX)
		cout << -1;
	else
		cout << A + 1 << ' ' << B + 1;
	*/
}