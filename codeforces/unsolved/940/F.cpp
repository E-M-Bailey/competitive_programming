#include <bits/stdc++.h>

using namespace std;

struct tree
{
	struct T
	{
		map<int, int>	F;
		array<int, 500> FF;
	};
	T f(T a, T b)
	{
		T ans;
		
	} // (any associative fn)
	vector<T> s;
	int		  n;
	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
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
	int n, q;
	cin >> n >> q;
	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N++;

	vector<int> A(n, 1);

	map<int, set<int>>				I;
	vector<vector<array<int, 500>>> T;

	for (int i = 0; i < n; i++)
		I[1].insert(i);

	T.emplace_back(N);
	for (int i = 0; i < n; i++)
		T.back()[i][1] = 1;
	for (int st = 2; (int)T.back().size() > 1; st *= 2)
	{
		vector<array<int, 500>> TT(T.back().size() / 2);
		for (int i = 0; i < (int)size(TT); i++)
		{
			TT[i][st] =
		}
	}

	vector<pair<int, int>> Q(q);
}
