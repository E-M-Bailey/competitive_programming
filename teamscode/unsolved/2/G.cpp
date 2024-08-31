#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x)		 begin(x), end(x)
#define sz(x)		 (int)(x).size()
typedef long long	   ll;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair

static char buf[450 << 20] alignas(32);
size_t buf_ind = sizeof buf;
void	   *operator new(size_t s)
{
	assert(s < buf_ind);
	return (void *)&buf[buf_ind -= s];
}
void operator delete(void *) {}
void operator delete(void *, size_t) {}


template<class T>
struct small
{
	typedef T value_type;
	small() {}
	template<class U>
	small(const U &)
	{}
	T *allocate(size_t n)
	{
		buf_ind -= n * sizeof(T);
		buf_ind &= 0 - alignof(T);
		return (T *)(buf + buf_ind);
	}
	void deallocate(T *, size_t) {}
};

template<typename T>
using vec = vector<T, small<T>>;
typedef vec<int> vi;

template<class T>
struct ptr
{
	unsigned ind;
	ptr(T *p = 0) : ind(p ? unsigned((char *)p - buf) : 0)
	{
		assert(ind < sizeof buf);
	}
	T &operator*() const
	{
		return *(T *)(buf + ind);
	}
	T *operator->() const
	{
		return &**this;
	}
	T &operator[](int a) const
	{
		return (&**this)[a];
	}
	explicit operator bool() const
	{
		return ind;
	}
};

struct Node
{
	ptr<Node> l = 0, r = 0;
	int		  lo, hi;
	long long madd = 0, val = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of -inf
	Node(vi &v, int lo, int hi) : lo(lo), hi(hi)
	{
		if (lo + 1 < hi)
		{
			int mid = lo + (hi - lo) / 2;
			l		= new Node(v, lo, mid);
			r		= new Node(v, mid, hi);
			val		= l->val + r->val;
		}
		else
			val = v[lo];
	}
	long long query(int L, int R)
	{
		if (R <= lo || hi <= L)
			return 0;
		if (L <= lo && hi <= R)
			return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void add(int L, int R, long long x)
	{
		if (R <= lo || hi <= L)
			return;
		if (L <= lo && hi <= R)
		{
			madd += x;
			val += x * (hi - lo);
		}
		else
		{
			push(), l->add(L, R, x), r->add(L, R, x);
			val = l->val + r->val;
		}
	}
	void push()
	{
		if (!l)
		{
			int mid = lo + (hi - lo) / 2;
			l		= new Node(lo, mid);
			r		= new Node(mid, hi);
		}
		if (madd)
			l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
	}
};

template<bool VALS_EDGES>
struct HLD
{
	int		  N, tim = 0;
	vec<vi>	  adj;
	vi		  par, siz, depth, rt, pos;
	ptr<Node> tree;
	HLD(vec<vi> adj_) : N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N), rt(N), pos(N), tree(new Node(0, N))
	{
		dfsSz(0);
		dfsHld(0);
	}
	void dfsSz(int v)
	{
		if (par[v] != -1)
			adj[v].erase(find(all(adj[v]), par[v]));
		for (int &u : adj[v])
		{
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]])
				swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v)
	{
		pos[v] = tim++;
		for (int u : adj[v])
		{
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template<class B>
	void process(int u, int v, B op)
	{
		for (; rt[u] != rt[v]; v = par[rt[v]])
		{
			if (depth[rt[u]] > depth[rt[v]])
				swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v])
			swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, long long val)
	{
		process(u,
				v,
				[&](int l, int r)
				{
					tree->add(l, r, val);
				});
	}
	long long queryPath(int u, int v)
	{ // Modify depending on problem
		long long res = 0;
		process(u,
				v,
				[&](int l, int r)
				{
					res = res + tree->query(l, r);
				});
		return res;
	}
	long long querySubtree(int v)
	{ // modifySubtree is similar
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

template<class T>
struct RMQ
{
	vec<vec<T>> jmp;
	RMQ(const vec<T> &V) : jmp(1, V)
	{
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
		{
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j, 0, sz(jmp[k])) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b)
	{
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

#define MAXN 300'010

vec<vi> adj;

bool present[MAXN];
ll	 vals[MAXN];
int	 vtype[MAXN];
pii	 path[MAXN];

int starting[MAXN];
int ending[MAXN];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);

	int n, m, q;
	cin >> n >> m >> q;
	adj.resize(n);

	rep(i, 0, n - 1)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	rep(i, 0, m)
	{
		int s, t, v, c;
		cin >> s >> t >> v >> c;
		s--;
		t--;
		vals[i] = v;
		if (c == 1)
			present[i] = true;

		path[i] = mp(s, t);
	}

	HLD<true>  vhld(adj);
	HLD<false> ehld(adj);
	rep(i, 0, m)
	{
		if (present[i])
		{
			vhld.modifyPath(path[i].first, path[i].second, vals[i]);
			ehld.modifyPath(path[i].first, path[i].second, -1 * vals[i]);
		}
	}

	while (q--)
	{
		int cmd;
		cin >> cmd;
		if (cmd == 1)
		{
			int i;
			cin >> i;
			i--;
			present[i] = true;
			vhld.modifyPath(path[i].first, path[i].second, vals[i]);
			ehld.modifyPath(path[i].first, path[i].second, -1 * vals[i]);
		}
		else if (cmd == 2)
		{
			int i;
			cin >> i;
			i--;
			present[i] = false;
			vhld.modifyPath(path[i].first, path[i].second, -1 * vals[i]);
			ehld.modifyPath(path[i].first, path[i].second, vals[i]);
		}
		else
		{
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			cout << -(vhld.queryPath(u, v) + ehld.queryPath(u, v)) << '\n';
		}
	}
}
