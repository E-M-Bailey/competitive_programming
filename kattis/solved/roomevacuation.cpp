/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/roomevacuation
TAGS: flow, maximum flow, dinic, unit capacities, graph, digraph, directed graph, simulation, grid, vertex capacity
EXPLANATION:
Overview: First, we construct a graph with O(nmt) vertices and edges, where each vertex corresponds to a specific
location and time and each edge corresponds to a the way an occupant could move at that point in time. Then, and show
how to reduce the problem to finding the maximum flow with edge capacities END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

template<class T>
constexpr T MAX = numeric_limits<T>::max();

struct edge
{
	int	 to;  // destination
	int	 idx; // index of reverse edge in adj[to]
	bool cap; // residual capacity
};

// Variant of Dinic's algorithm.
// A simplified version of https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/Dinic.h
// The version on KACTL runs in O(V E log U), where U is an upper bound on flow and is assumed to be about 2^30.
// The for-loop that causes the different complexity has been removed from this version, since the change is useless for
// unit-capacity networks. This version *should* (I'm not 100% sure) have the same time complexity as the usual version
// of Dinic's algorithm, including for unit-capacity networks.
struct dinic
{
	// Queue used for finding blocking flows with BFS.
	deque<int> bfs;
	// Each vertex's BFS level, or 0 if it hasn't been visited yet in the current iteration.
	vector<int> level;
	// Number of edges each vertex has already considered in this iteration.
	vector<int> idx;
	// Residual network.
	vector<vector<edge>> adj;
	// Start and end point of the flow.
	int source, sink;
	dinic(int n, int source, int sink) : level(n), idx(n), adj(n), source(source), sink(sink) {}
	// Adds a from->to edge with capacity 1 its reverse with capacity 0 to the residual graph.
	void add(int from, int to)
	{
		edge fromTo{to, (int)size(adj[to]), true};
		edge toFrom{from, (int)size(adj[from]), false};
		adj[from].push_back(fromTo);
		adj[to].push_back(toFrom);
	}

	// Looks for an augmenting path in the layered network.
	// Augments the network and returns true iff one is found.
	bool dfs(int from)
	{
		// Base case
		if (from == sink)
			return true;
		// Iterate over adjacent vertices in the residual graph, skipping those already considered this iteration.
		for (; idx[from] < (int)size(adj[from]); idx[from]++)
		{
			auto &[to, j, cap] = adj[from][idx[from]];
			// Only consider edges with positive capacity in the layered graph from which a positive-capacity path to
			// the sink can be found.
			if (cap && level[to] == level[from] + 1 && dfs(to))
			{
				// An augmenting path has been found, so augment this edge and return true.
				cap			   = false;
				adj[to][j].cap = true;
				return true;
			}
		}
		// No augmenting from->sink path in the level graph.
		return false;
	}

	// Computes the maximum flow in the network from source to sink.
	int flow()
	{
		int flow = 0;

		// For non-unit capacities, this would be enclosed in a for loop, which is the source of the O(log U) in the
		// time complexity. See the KACTL implementation for an example.
		do
		{
			// Reset level and idx
			fill(begin(level), end(level), 0);
			level[source] = 1;
			fill(begin(idx), end(idx), 0);

			// Enqueue the source
			bfs.push_back(source);
			while (!bfs.empty() && level[sink] == 0)
			{
				// Dequeue the current vertex
				int from = bfs.front();
				bfs.pop_front();
				// For each outgoing edge with positive capacity to an unvisited vertex...
				for (auto [to, idx, cap] : adj[from])
				{
					if (cap && level[to] == 0)
					{
						// ... put it in the next level and enqueue it.
						level[to] = level[from] + 1;
						bfs.push_back(to);
					}
				}
			}
			bfs.clear();
			// Augment the residual graph with a blocking flow.
			// This is done by repeatedly finding augmenting paths in the layered graph until none exist.
			while (dfs(source))
				flow++;
			// Iterate until the BFS terminates without reaching the sink.
			// This happens only once the sink is disconnected and the flow is maximized
		}
		while (level[sink] != 0);
		return flow;
	}
};

// Legal moves
constexpr array<pair<int, int>, 5> DIR{
	make_pair(-1, 0),
	make_pair(0, -1),
	make_pair(1, 0),
	make_pair(0, 1),
	make_pair(0, 0),
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	// Parse input
	int n, m, t;
	cin >> n >> m >> t;
	vector<string> grid(n);
	for (string &row : grid)
		cin >> row;

	// Nodes are ordered by row, then column, then time, followed by the source and the sink.
	int N	   = n * m * (t + 1) * 2 + 2;
	int source = N - 2, sink = N - 1;
	// The index of the virtual vertex at cell (i, j) and time k. If u = idx(i, j, k), the vertices for
	//     incoming and outgoing edges making up this virtual vertex are 2u and 2u+1, respectively.
	const auto index = [n, m, t](int i, int j, int k)
	{
		return k + (t + 1) * (j + m * i);
	};

	dinic D(N, source, sink);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k <= t; k++)
			{
				char cell = grid[i][j];
				// Current vertex.
				int from = index(i, j, k), fromIn = 2 * from, fromOut = 2 * from + 1;
				// Edge simulating vertex capacity.
				D.add(fromIn, fromOut);

				// If not from an exit, an obstacle, or the last time slice...
				if (cell != 'E' && cell != '#' && k < t)
					// ... to each reachable cell in the next time slice...
					for (auto [di, dj] : DIR)
					{
						int i2 = i + di, j2 = j + dj;
						// ... except positions outside the grid and obstacles...
						if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m || grid[i2][j2] == '#')
							continue;
						// ... add an edge.
						int to = index(i2, j2, k + 1), toIn = 2 * to;
						D.add(fromOut, toIn);
					}
				// Connect the source to each person's starting point in the first time slice
				if (cell == 'P' && k == 0)
					D.add(source, fromIn);
				// Connect each exit to the sink at every time slice
				if (cell == 'E')
					D.add(fromOut, sink);
			}
	cout << D.flow() << '\n';
}
