#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 998244353;

int64_t mpow(int64_t a, int64_t b)
{
	int64_t ans = 1;
	for (a %= MOD, b %= MOD - 1; b; a = a * a % MOD, b /= 2)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

struct dso
{
	vector<int> P, S, V;
	dso(int n) : P(n), S(n), V(n)
	{
		iota(begin(P), end(P), 0);
		iota(begin(V), end(V), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = { P[x], P[P[x]] };
		return x;
	}
	int onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x != y)
		{
			if (S[x] < S[y])
				swap(x, y);
			S[x] += S[y];
			P[y] = x;
		}
		return x;
	}
};

int n;
vector<vector<int>> C;
vector<int> S;
vector<int> ans;

void dfs(int v, int pr)
{
	if (v < n)
		ans[v] = pr;
	else
	{
		int l = C[v][0], r = C[v][1];
		int64_t d = mpow(S[v], MOD - 2);
		dfs(l, int((pr + S[l] * d) % MOD));
		dfs(r, int((pr + S[r] * d) % MOD));
	}
}

int main()
{
	cin >> n;

	dso D(n);
	C.resize(n * 2 - 1);
	S.resize(n * 2 - 1, 1);
	ans.resize(n);

	for (int i = 0; i < n - 1; i++)
	{
		int p, q;
		cin >> p >> q;
		p = D.find(p - 1);
		q = D.find(q - 1);
		int r = i + n;
		C[r] = { D.V[p], D.V[q] };
		S[r] = S[D.V[p]] + S[D.V[q]];
		D.V[D.onion(p, q)] = r;
	}

	dfs(2 * n - 2, 0);
	for (int a : ans)
		cout << a << ' ';
}