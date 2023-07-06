/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/abinitio
TAGS: graph, digraph, directed graph, adjacency matrix, matrix, implementation, mod, modular arithmetic, hash, hashing
EXPLANATION:
One way to solve this problem is to maintain an adjacency matrix. Every operation can be implemented in a simple loop that
modifies this matrix in O(V) or O(1), except complement and transpose, which both take Θ(n^2) to do naively.

To fix this, also maintain two boolean flags, which store whether the graph is complemented/transposed respectively. Complement
and transpose are now O(1), since they just need to toggle their flags. Now, in the other operations, whenever querying or setting
a value in the adjacency matrix, we need to check these flags. If the complemented flag is set, the queried or set value must be
toggled, simulating the graph being complemented. Similarly, if the transposed flag is set, the row and column index of these
operations must be swapped, simulating the adjacency matrix being transposed. (The only exception is that a vertex is never
adjacent to itself, regardless of whether the graph is complemented.)

With this idea, each operation can be implemented in O(V), leading to a total runtime of O(VQ), which is fast enough. When
calculating the hashes, be sure to use 64-bit integers and take intermediate results modulo 1e9+7 to avoid overflow.
END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int n = 0;
bool adj[4000][4000]{};
bool complemented = false, transposed = false;

bool is_adj(int i, int j)
{
	if (i == j)
		return false; // No self-loops even when complemented
	return complemented ^ (transposed ? adj[j][i] : adj[i][j]);
}
void set_adj(int i, int j, bool val)
{
	(transposed ? adj[j][i] : adj[i][j]) = val ^ complemented;
}

void add_vertex()
{
	for (int i = 0; i < n; i++)
	{
		set_adj(i, n, false);
		set_adj(n, i, false);
	}
	n++;
}
void add_edge(int x, int y)
{
	set_adj(x, y, true);
}
void del_all(int x)
{
	for (int i = 0; i < n; i++)
	{
		set_adj(i, x, false);
		set_adj(x, i, false);
	}
}
void del_edge(int x, int y)
{
	set_adj(x, y, false);
}
void transpose()
{
	transposed ^= true;
}
void complement()
{
	complemented ^= true;
}
pair<int, int> deg_hash(int x)
{
	long long deg = 0, hash = 0, p7 = 1;
	for (int i = 0; i < n; i++)
		if (is_adj(x, i))
		{
			deg++;
			hash = (hash + p7 * i) % MOD;
			p7 = p7 * 7 % MOD;
		}
	return { (int)deg, (int)hash };
}

int main()
{
	int v, e, w;
	cin >> v >> e >> w;
	for (int i = 0; i < v; i++)
		add_vertex();
	for (int i = 0; i < e; i++)
	{
		int A, B;
		cin >> A >> B;
		add_edge(A, B);
	}
	for (int i = 0; i < w; i++)
	{
		int t, x, y;
		cin >> t;
		switch (t)
		{
		case 1:
			add_vertex();
			break;
		case 2:
			cin >> x >> y;
			add_edge(x, y);
			break;
		case 3:
			cin >> x;
			del_all(x);
			break;
		case 4:
			cin >> x >> y;
			del_edge(x, y);
			break;
		case 5:
			transpose();
			break;
		case 6:
			complement();
			break;
		}
	}

	cout << n << '\n';
	for (int i = 0; i < n; i++)
	{
		auto [deg, hash] = deg_hash(i);
		cout << deg << ' ' << hash << '\n';
	}
}
