#include <bits/stdc++.h>

using namespace std;

// graph, DFS numbers, articulation point indices, biconnected components, edge stack, parent, vertex, num counter, art counter, bcc counter -> lowpoint
int dfs1(vector<vector<int>> const &adj, vector<int> &num, vector<int> &art, vector<unordered_set<int>> &bcc, vector<pair<int, int>> &st, int u, int v, int &t, int &a, int &b) {
	int low_v = num[v] = t++, low_w, first = true;
	for (int w : adj[v])
		if (w == u) {} // skip the parent
		else if (num[w] == -1) { // unvisited
			auto sz = st.size();
			st.emplace_back(v, w);
			low_v = min(low_v, low_w = dfs1(adj, num, art, bcc, st, v, w, t, a, b));
			if (low_w >= num[v]) { // articulation point or root
				for (; st.size() > sz; st.pop_back()) // pop edges of the bcc
					bcc[st.back().first].insert(b), bcc[st.back().second].insert(b);
				if (art[v] == -1 && (v != u || !first)) // root needs multiple children 
					art[v] = a++;
				first = false, b++;
			}
		}
		else if (low_v = min(low_v, num[w]), num[w] < num[v])
			st.emplace_back(v, w);
	return low_v;
}

struct dsu {
	vector<int> P, R, anc, vis, D; // parent, rank, ancestor, visited?, depth
	dsu(int n) : P(n), R(n), vis(n), D(n) { iota(begin(P), end(P), 0); anc = P; }
	int find(int x) {
		while (x != P[x]) tie(x, P[x]) = pair(P[x], P[P[x]]);
		return x;
	}
	int merge(int x, int y) {
		if (R[x = find(x)] < R[y = find(y)]) swap(x, y);
		P[y] = x, R[x] += R[x] == R[y];
		return x;
	}
}; // Tarjan's Offline LCA
void dfs2(vector<vector<int>> const &adj, vector<vector<int>> const &Q, dsu &D, vector<unordered_map<int, int>> &L, int u, int v) {
	for (int w : adj[v])
		if (w != u)
			D.D[w] = D.D[v] + 1, dfs2(adj, Q, D, L, v, w), D.anc[D.merge(v, w)] = v;
	D.vis[v] = true;
	for (int w : Q[v])
		if (D.vis[w]) L[v][w] = L[w][v] = D.anc[D.find(w)];
}

int main() { // t, a, b: counters for DFS num, articulation point index, and BCC index
	int n, m, q, t = 0, a = 0, b = 0, x, y; cin >> n >> m >> q;
	vector<vector<int>> adj(n), bct(n * 2), Q(n * 2); // graph, block-cut tree, LCA queries
	vector<tuple<int, int, int, int, int, int>> X(q); // queries
	vector<int> num(n, -1), art(n, -1); // DFS numbers, articulation point indices
	vector<unordered_set<int>> bcc(n); vector<pair<int, int>> st; // BCC indices, edge stack
	for (int i = 0; i < m; i++) cin >> x >> y, adj[x - 1].push_back(y - 1), adj[y - 1].push_back(x - 1);
	if (adj[0].empty()) bcc[0].insert(b); // isolated vertex
	else dfs1(adj, num, art, bcc, st, 0, 0, t, a, b); // unvisited
	for (int v = 0; v < n; v++) if (art[v] >= 0) // block-cut tree
		for (int w : bcc[v]) bct[art[v]].push_back(w + a), bct[w + a].push_back(art[v]);
	for (auto &[qa, qb, qc, A, B, C] : X) {
		cin >> qa >> qb >> qc, A = *begin(bcc[--qa]) + a, B = *begin(bcc[--qb]) + a, C = art[--qc];
		if (qa != qc && qb != qc && C >= 0) // query lca(A, B), lca(A, C), and lca(B, C) if the answer isn't trivial
			Q[A].push_back(B), Q[A].push_back(C), Q[B].push_back(A), Q[B].push_back(C), Q[C].push_back(A), Q[C].push_back(B);
	}
	dsu D(a + b); vector<unordered_map<int, int>> L(a + b); // DSU, LCA query results
	dfs2(bct, Q, D, L, 0, 0); // Compute LCAs
	for (auto [qa, qb, qc, A, B, C] : X)
		cout << (qa == qc || qb == qc || (C >= 0 && (L[A][C] == C || L[B][C] == C) && D.D[C] >= D.D[L[A][B]]) ? "NO\n" : "YES\n");
}