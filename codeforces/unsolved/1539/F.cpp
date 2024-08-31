#include <bits/stdc++.h>

using namespace std;

struct tree
{
	struct T
	{
		int sum, pre, suf;
		constexpr T(int x = 0) : sum(x), pre(max(x, 0)), suf(max(x, 0)) {}
		T(int x, int p, int s) : sum(x), pre(p), suf(s) {}
	};
	T f(T a, T b)
	{
		return {a.sum + b.sum, max(a.pre, a.sum + b.pre), max(b.suf, b.sum + a.suf)};
	}
	int		  n;
	vector<T> s;
	tree(int N) : n(N), s(2 * n) {}
	void upd(int i, T x)
	{
		for (s[i += n] = x; i /= 2;)
			s[i] = f(s[i * 2], s[i * 2 + 1]);
	}
	T qry(int l, int r)
	{
		T a, b;
		for (l += n, r += n; l < r; l /= 2, r /= 2)
		{
			if (l % 2)
				a = f(a, s[l++]);
			if (r % 2)
				b = f(s[--r], b);
		}
		return f(a, b);
	}
};

template<bool CEIL>
void solve(int n, vector<vector<int>> &B, vector<int> &ans)
{
	tree T(n);
	for (int i = 0; i < n; i++)
		T.upd(i, {-1});

	for (int a = 0; a < n; a++)
	{
		for (int i : B[a])
			T.upd(i, {1});
		for (int i : B[a])
			ans[i] = max(ans[i], (T.qry(0, i).suf + T.qry(i + 1, n).pre + CEIL) / 2);
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<vector<int>> B(n);
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		B[--a].push_back(i);
	}

	vector<int> ans(n);
	solve<0>(n, B, ans);
	reverse(begin(B), end(B));
	solve<1>(n, B, ans);

	for (int a : ans)
		cout << a << ' ';
}
