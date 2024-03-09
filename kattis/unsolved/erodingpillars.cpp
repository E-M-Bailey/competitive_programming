#include <bits/stdc++.h>
using namespace std;

/*
struct point
{
	int x, y;
};
uint64_t dist2(const point& a, const point& b)
{
	uint64_t dx = b.x - a.x, dy = b.y - a.y;
	return dx * dx + dy * dy;
}

struct edge
{
	int v, id;
};

int n;
vector<point> P;
int ctr = 0;
vector<vector<edge>> G;
vector<int> num;
stack<int, vector<int>> st;
vector<bool> M;
int t = 0;
void reset()
{
	ctr = 0;
	for (auto& GG : G)
		GG.clear();
	fill(begin(num), end(num), 0);
	fill(begin(M), end(M), false);
	t = 0;
}
void add(int u, int v)
{
	G[u].emplace_back(u, ctr);
	G[v].emplace_back(v, ctr);
	ctr++;
}

// Mark every vertex biconnected with the root; based on KACTL's implementation
int dfs(int u, int v)
{
	int me = num[v] = ++t;
	int top = me;
	for (auto [y, e] : G[v])
		if (e != u)
		{
			if (num[y] > 0)
			{
				top = min(top, num[y]);
				if (num[y] < me)
					st.push(e);
			}
			else
			{
				int si = size(st);
				int up = dfs(e, y);
				top = min(top, up);
				if (up == me) // the elements added to st by up form a BCC
				{
					st.push(e);
					while (st.size() > si)
						st.pop();
				}
			}
		}
}

bool works(uint64_t d2)
{
	// Build graph
	reset();
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (dist2(P[i], P[j]) <= d2)
				add(i, j);

}

int main()
{
	cin >> n;
	n++;
	P.resize(n);
	G.resize(n);
	num.resize(n);
	M.resize(n);
	P[0] = { 0, 0 };
	for (int i = 1; i < n; i++)
		cin >> P[i].x >> P[i].y;

	// Binary search on distance squared
	// 9e18 > (2e9*sqrt(2))^2
	uint64_t lo = 1, hi = 9'000'000'000'000'000'000ull;
	while (lo < hi)
	{
		uint64_t d2 = (lo + hi) / 2;
		if (works(d2))
			hi = d2;
		else
			lo = d2 + 1;
	}
	cout << fixed << setprecision(7) << sqrtl(lo)
}
*/

struct DFS
{
	// Vertex count, next DFS number
	int n, t;
	// Limit on squared distance
	int64_t d2;
	// DFS numbers and lowpoints
	vector<int> num, lo;
	// Vertices biconnected to the DFS root
	vector<bool> mark;
	// Coordinates
	vector<pair<int, int>> X;

	DFS(vector<pair<int, int>>&& X):
		n(X.size()),
		num(n),
		lo(n),
		mark(n),
		X(forward<vector<pair<int, int>>>(X))
	{}

	void dfs(int u, int v)
	{
		// Assign the next DFS number
		lo[v] = num[v] = t++;
		auto [x1, y1] = X[v];
		for (int w = 0; w < n; w++)
		{
			// Skip parent
			if (w == u)
				continue;
			auto [x2, y2] = X[w];
			int64_t dx = x1 - x2, dy = y1 - y2;
			// Skip edges that are too long
			if (dx * dx + dy * dy > d2)
				continue;
			// Downward edges
			if (num[w] == -1)
			{

			}
			// Back-edges
			else
			{

			}
		}
	}
};
void dfs(int u, int v, int& t, vector<int>& num, vector<int>& lo, vector<bool>& mark)
{
	// Assign next DFS number
	lo[v] = num[v] = t++;
	for (int w = 0; w)
}

int main()
{
	int n;
	cin >> n;
	n++;
	vector<pair<int, int>> X(n);
	for (int i = 1; i < n; i++)
		cin >> X[i].first >> X[i].second;

}