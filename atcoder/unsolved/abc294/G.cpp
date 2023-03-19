#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2e5, MAXJ = 20;
int n;
int PA[MAXN];
vector<int> C[MAXN]{};
int S[MAXN];
int D[MAXN];
int U[MAXN - 1], V[MAXN - 1], W[MAXN - 1];
int T[MAXN], O[MAXN], PP[MAXN];
int E[MAXN * 2], TE[MAXN];
int64_t S[MAXN]{};

void fupd(int i, int64_t d)
{
	for (; i < MAXN; i |= i + 1)
		S[i] += d;
}
int64_t fqry(int i)
{
	int64_t ans = 0;
	for (; i > 0; i &= i - 1)
		ans += S[i - 1];
	return ans;
}

int J[MAXJ][MAXN];

bool cmp(int v, int w)
{
	return D[v] < D[w];
}

void rinit(const vector<int>& V)
{
	copy(begin(V), end(V), J[0]);
	for (int pw = 1, k = 1; pw * 2 <= size(V); pw *= 2, ++k)
	{
		int s = size(V) - pw * 2 + 1;
		for (int j = 0; j < s; j++)
			J[k][j] = min(J[k - 1][j], J[k - 1][j + pw], &cmp);
	}
}
int rqry(int a, int b)
{
	assert(a < b);
	int dep = 31 - __builtin_clz(b - a);
	return min(J[dep][a], J[dep][b - (1 << dep)], &cmp);
}

/*
struct Tree
{
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); }
	vector<T> s; int n;
	Tree(int n = 0, T def = unit): s(2 * n, def), n(n) {}
	void update(int pos, T val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e)
	{
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2)
		{
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};*/



void dfs1(int u, int v, int d)
{
	if (u >= 0)
		C[v].erase(find(begin(C[v]), end(C[v]), u));
	PA[v] = u;
	D[v] = d;
	S[v] = 1;
	for (int w : C[v])
	{
		dfs1(v, w, d + 1);
		S[v] += S[w];
	}
	sort(begin(C[v]), end(C[v]), [](int x, int y) { return S[x] > S[y]; });
}

pair<int, int> dfs2(int v, int t, int pp, int te)
{
	T[v] = t;
	PP[t] = O[pp];
	O[t++] = v;
	TE[v] = te;
	E[te++] = v;
	for (int w : C[v])
	{
		tie(t, te) = dfs2(w, t, w == C[v].front() ? pp : w);
		E[te++] = v;
	}
	return { t, te };
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> U[i] >> V[i] >> W[i];
		U[i]--;
		V[i]--;
		C[U[i]].push_back(V[i]);
		C[V[i]].push_back(U[i]);
	}

	dfs1(-1, 0, 0);
	dfs2(0, 0, 0);


}