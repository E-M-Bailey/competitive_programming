#include <bits/stdc++.h>

using namespace std;

static constexpr const int iinf = 1e9 + 10;
using ll = long long;

struct edge {
	int u, v, w;
};

struct DSU {
	vector<int> dsu;
	explicit DSU(int n) : dsu(n, -1) {}
	int find(int u) {
		if (dsu[u] < 0) return u;
		return dsu[u] = find(dsu[u]);
	}
	bool merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return false;
		if (dsu[u] > dsu[v]) swap(u, v);
		dsu[u] += dsu[v];
		dsu[v] = u;
		return true;
	}
};

template <class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ() = default;
	void initialize(const vector<T>& V) {
		jmp.assign(1, V);
		for (int pw = 1, k = 1; pw * 2 <= int(V.size()); pw *= 2, k++) {
			jmp.emplace_back(int(V.size()) - pw * 2 + 1);
			for (int j = 0; j<int(jmp[k].size()); j++) {
				jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
			}
		}
	}
	T query(int a, int b) {
		assert(a < b);
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b]);
	}
};

struct MergeSortTree {
	vector<vector<edge>> tree;
	vector<RMQ<int>> rmq;
	explicit MergeSortTree(int n) : tree(4*n), rmq(4 * n) {}
	void insert(int idx, int curr_l, int curr_r, int i, const edge& e) {
		if (curr_l == curr_r) {
			tree[idx].push_back(e);
			return;
		}
		auto mid = curr_l + (curr_r - curr_l) / 2;
		if (i <= mid) {
			insert(idx*2+1, curr_l, mid, i, e);
		} else {
			insert(idx*2+2, mid+1, curr_r, i, e);
		}
		tree[idx].push_back(e);
	}
	void build(int idx, int curr_l, int curr_r) {
		if (curr_l > curr_r) return;
		vector<int> w;
		for (const auto& e : tree[idx]) {
			w.push_back(e.w);
		}
		rmq[idx].initialize(w);
		auto mid = curr_l + (curr_r - curr_l) / 2;
		build(idx*2+1, curr_l, mid);
		build(idx*2+2, mid+1, curr_r);
	}
	int query(int idx, int curr_l, int curr_r, int lx, int rx, int ly, int ry) {
		if (curr_l > curr_r || rx < curr_l || curr_r < lx) return iinf;
		if (lx <= curr_l && curr_r <= rx) {
			int low = 0, high =  int(tree[idx].size())-1;
			int lb = -1, rb = -1;
			// find first position >= ly
			while (low <= high) {
				auto mid = low + (high - low) / 2;
				if (tree[idx][mid].v >= ly) {
					lb = mid;
					high = mid-1;
				} else {
					low = mid + 1;
				}
			}
			low = 0, high = int(tree[idx].size())-1;
			while (low <= high) {
				auto mid = low + (high - low) / 2;
				if (tree[idx][mid].v <= ry) {
					rb = mid;
					low = mid + 1;
				} else {
					high = mid-1;
				}
			}
			if (lb == -1 || rb == -1 || lb >= rb) return iinf;
			return rmq[idx].query(lb, rb + 1);
		}
		auto mid = curr_l + (curr_r - curr_l) / 2;
		auto left = query(idx*2+1, curr_l, mid, lx, rx, ly, ry);
		auto right = query(idx*2+2, mid+1, curr_r, lx, rx, ly, ry);
		return min(left, right);
	}
};



int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n,m;
	cin >> n >> m;
	vector<edge> edges, extra_edges, used_edges;
	DSU dsu{n};
	vector<vector<pair<int, int>>> mst(n);
	ll kruskal_cost = 0;

	for (int i = 0; i<m; i++) {
		int u,v,w;
		cin >> u >> v >> w;
		edges.push_back({u, v, w});
	}
	sort(edges.begin(), edges.end(), [](const auto& x, const auto& y) {
		return x.w < y.w; 
	});

	for (auto& [u, v, w] : edges) {
		if (!dsu.merge(--u, --v)) {
			extra_edges.push_back({u, v, w});
		} else {
			mst[u].emplace_back(v, w);
			mst[v].emplace_back(u, w);
			kruskal_cost += w;
			used_edges.push_back({u, v, w});
		}
	}

	cerr << "kruskal: " << kruskal_cost << '\n';
	vector<int> tin(n, -1), tout(n, -1);
	int timer = 0;
	function<void(int, int)> dfs = [&](int curr, int par) {
		tin[curr] = timer++;
		for (const auto& [neighbor, _] : mst[curr]) {
			if (neighbor != par) {
				dfs(neighbor, curr);
			}
		}
		tout[curr] = timer;
	};
	dfs(0, -1);
	MergeSortTree tree{int(extra_edges.size())};
	for (auto& e : extra_edges) {
		if (tin[e.u] > tin[e.v]) swap(e.u, e.v);
		e.u = tin[e.u];
		e.v = tin[e.v];
	}
	sort(extra_edges.begin(), extra_edges.end(), [](const auto& x, const auto& y) {
		return make_pair(x.u, x.v) < make_pair(y.u, y.v);
	});
	for (int i = 0; i<int(extra_edges.size()); i++) {
		tree.insert(0, 0, int(extra_edges.size())-1, i, extra_edges[i]);
	}
	ll ret = kruskal_cost;
	for (auto& e : used_edges) {
		if (tin[e.u] > tin[e.v]) swap(e.u, e.v);
		int low = 0, high = int(extra_edges.size())-1;
		int lb = -1, rb = -1;
		// find range [tin[e.v], tout[e.v]-1]
		while (low <= high) {
			auto mid = low + (high - low) / 2;
			if (extra_edges[mid].u >= tin[e.v]) {
				lb = mid;
				high = mid-1;
			} else {
				low = mid + 1;
			}
		}
		low = 0, high = int(extra_edges.size())-1;
		while (low <= high) {
			auto mid = low + (high - low) / 2;
			if (extra_edges[mid].u < tout[e.v]) {
				rb = mid;
				low = mid + 1;
			} else {
				high = mid-1;
			}
		}
		if (lb == -1 || rb == -1 || lb > rb) continue;
		auto sol1 = tree.query(0, 0, int(extra_edges.size())-1, 0, lb-1, tin[e.v], tout[e.v]-1);
		cerr << "sol1(0, " << lb-1 << ", " << tin[e.v] << ", " << tout[e.v]-1 <<"): " << sol1 << '\n'; 
		auto sol2 = tree.query(0, 0, int(extra_edges.size())-1, lb, rb, tout[e.v], n-1);
		cerr << "sol2(" << lb << ", " << rb << ", " << tout[e.v] << ", " << n-1 <<"): " << sol2 << '\n'; 
		cerr << "e = (" << e.u << " " << e.v << " " << e.w << '\n';
		ret = max(ret, kruskal_cost + min(sol1, sol2) - e.w);
	}
	cout << ret << '\n';
}