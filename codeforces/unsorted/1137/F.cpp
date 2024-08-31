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
	// cin >> tc;
	while (tc--)
		go();
}

struct FT
{
	vector<int> s;
	FT(int n = 0) : s(n) {}
	void update(int pos, int dif)
	{
		for (; pos < (int)size(s); pos |= pos + 1)
			s[pos] += dif;
	}
	int query(int pos)
	{
		int res = 0;
		for (; pos > 0; pos &= pos - 1)
			res += s[pos - 1];
		return res;
	}
};

FT freq;

mt19937_64							randy;
uniform_int_distribution<long long> p_distr(LLONG_MIN, LLONG_MAX);

int n;

struct treaps
{
	struct node
	{
		long long p;
		int		  l, r, pa;
		int		  pp;
		int		  c;
		int		  pv;
		bool	  rv;
	};

	vector<node> N;

	int mk()
	{
		int		  pos = (int)size(N);
		long long p	  = p_distr(randy);
		N.push_back({p, -1, -1, -1, -1, 1, pos, false});
		return pos;
	};

	void rev(int v)
	{
		if (v >= 0)
			N[v].rv ^= true;
	}
	void set(int v, int p)
	{
		if (v >= 0)
			N[v].pv = p;
	}
	int num(int v)
	{
		return v >= 0 ? N[v].c : 0;
	}
	int pri(int v)
	{
		return v >= 0 ? N[v].pv : -1;
	}

	void push(int v)
	{
		if (v < 0)
			return;
		if (N[v].rv)
		{
			N[v].rv = false;
			swap(N[v].l, N[v].r);
			rev(N[v].l);
			rev(N[v].r);
		}
		set(N[v].l, N[v].pv);
		set(N[v].r, N[v].pv);
	}

	void fix(int v)
	{
		if (v < 0)
			return;
		if (N[v].pa >= 0 && N[N[v].pa].l != v && N[N[v].pa].r != v)
			exit(-3);
		N[v].c = 1 + num(N[v].l) + num(N[v].r);
	}

	int root(int v)
	{
		if (v < 0)
			return -1;
		while (N[v].pa >= 0)
			v = N[v].pa;
		return v;
	}
	pair<int, int> index_of(int v)
	{
		if (v < 0)
			return {-1, -1};
		vector<int> path{v};
		while (N[path.back()].pa >= 0)
			path.push_back(N[path.back()].pa);
		int k = (int)size(path);

		int ans = 0;
		for (int i = k; i-- > 1;)
		{
			push(path[i]);
			if (path[i - 1] == N[path[i]].r)
				ans += num(N[path[i]].l) + 1;
		}
		push(v);
		ans += num(N[v].l);
		return {ans, path.back()};
	}
	int at_index(int v, int i)
	{
		if (v < 0 || i >= num(v))
			return -1;
		push(v);

		int nl = num(N[v].l), ans;
		if (i < nl)
			ans = at_index(N[v].l, i);
		else if (i == nl)
			ans = v;
		else
			ans = at_index(N[v].r, i - nl - 1);

		return ans;
	}
	pair<int, int> split(int v, int i)
	{
		if (v < 0 || i == 0)
			return {-1, v};
		else if (i >= N[v].c)
			return {v, -1};

		int nl = num(N[v].l);
		if (i <= nl)
		{
			push(v);
			auto [a, b] = split(N[v].l, i);
			N[v].l		= b;
			if (a >= 0)
				N[a].pa = -1;
			if (b >= 0)
				N[b].pa = v;
			fix(v);
			return {a, v};
		}
		else
		{
			push(v);
			auto [a, b] = split(N[v].r, i - nl - 1);
			N[v].r		= a;
			if (b >= 0)
				N[b].pa = -1;
			if (a >= 0)
				N[a].pa = v;
			fix(v);
			return {v, b};
		}
	}
	int join(int l, int r)
	{
		if (l < 0)
			return r;
		if (r < 0)
			return l;

		if (N[l].pv != N[r].pv)
			exit(-4);

		if (N[l].p < N[r].p)
		{
			push(r);
			N[r].l = join(l, N[r].l);
			if (N[r].l >= 0)
				N[N[r].l].pa = r;
			fix(r);
			return r;
		}
		else
		{
			push(l);
			N[l].r = join(N[l].r, r);
			if (N[l].r >= 0)
				N[N[l].r].pa = l;
			fix(l);
			return l;
		}
	}
};

vector<vector<int>> G;

treaps T;
int	   root, ctr;

int dfs(int v, int u = -1)
{
	int mr = -1;
	for (int w : G[v])
	{
		if (w == u)
			continue;
		int wr = dfs(w, v);
		if (T.N[v].pv < T.N[wr].pv)
		{
			T.N[v].pv = T.N[wr].pv;
			mr		  = wr;
		}
		T.N[w].pp = v;
	}

	freq.update(T.N[v].pv, 1);
	return T.join(mr, v);
}

void up(int v)
{
	if (v == root)
		return;
	auto [iv, rv]  = T.index_of(v);
	auto [av, bcv] = T.split(rv, iv);
	if (av >= 0)
		T.N[T.at_index(av, T.N[av].c - 1)].pp = v;
	auto [bv, cv] = T.split(bcv, 1);
	if (bv != v)
		exit(bv);
	if (cv >= 0)
		T.N[v].pp = T.at_index(cv, 0);

	int			cur = ctr++;
	vector<int> path{v};
	while (path.back() != root)
	{
		if (path.back() < 0)
			exit(-6);
		int u		  = T.N[T.at_index(path.back(), T.N[path.back()].c - 1)].pp;
		auto [iu, ru] = T.index_of(u);
		auto [au, bu] = T.split(ru, iu);
		if (au >= 0)
			T.N[T.at_index(au, T.N[au].c - 1)].pp = u;
		path.push_back(bu);
	}

	for (int w : path)
	{
		int np = w == v ? cur : cur - 1;
		freq.update(T.N[w].pv, -T.N[w].c);
		freq.update(np, T.N[w].c);
		T.N[w].pv = np;
	}
	int r = -1;
	for (int i = 1; i < (int)size(path); i++)
		r = T.join(r, path[i]);

	T.rev(r);
	int ch = T.at_index(r, T.N[r].c - 1);
	if (ch >= 0)
		T.N[ch].pp = v;
	root = v;
}

int when(int v)
{
	auto [iv, rv] = T.index_of(v);
	int fq		  = freq.query(T.N[rv].pv);
	return iv + fq;
}

void go()
{
	long long seed =
		chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
	randy.seed(seed);

	int q;
	cin >> n >> q;

	freq = FT(n + q);

	G.resize(n);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for (int i = 0; i < n; i++)
		T.mk();

	root = n - 1;
	dfs(root);

	ctr = n;
	while (q--)
	{
		string cmd;
		int	   v;
		cin >> cmd >> v;
		v--;
		if (cmd == "up")
			up(v);
		else if (cmd == "when")
			cout << when(v) + 1 << '\n';
		else
		{
			int u;
			cin >> u;
			u--;
			cout << (when(v) < when(u) ? v : u) + 1 << '\n';
		}
	}
}
