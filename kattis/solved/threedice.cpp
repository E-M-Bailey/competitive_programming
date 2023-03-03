#include <bits/stdc++.h>
using namespace std;

void fail()
{
	cout << 0 << endl;
	exit(0);
}

unordered_map<char, int> ID;
int id(char c)
{
	return ID.try_emplace(c, size(ID)).first->second;
}

// Adjacency matrix with bitmasks
array<int, 26> G{};
void add(int u, int v)
{
	// duplicate letters => no solution
	if (u == v)
		fail();
	G[u] |= 1 << v;
	G[v] |= 1 << u;
}

// Print the dice corresponding to this coloring.
void print(const array<int, 3>& M)
{
	array<string, 3> S;
	for (auto [c, id] : ID)
	{
		// Add this char to the string corresponding to the set its id is in
		int m = 1 << id;
		for (int k = 0; k < 3; k++)
			if (M[k] & m)
				S[k] += c;
	}
	for (const string& s : S)
		cout << s << ' ';
}

// Recursively search for a balanced 3-coloring, pruning early when the current path is known to be impossible.
// params are current node
bool rec(int i, array<int, 3>& M)
{
	// Success! All nodes have a color, so print the solution.
	if (i == 18)
	{
		print(M);
		return true;
	}

	for (int k = 0; k < 3; k++)
	{
		// Can't already have 6 nodes or have neighbors of node i.
		if (__builtin_popcount(M[k]) == 6 || M[k] & G[i])
			continue;
		M[k] ^= 1 << i;
		if (rec(i + 1, M))
			return true;
		M[k] ^= 1 << i;
	}
	return false;
}

int main()
{
	int n;
	cin >> n;
	// Build graph
	for (int i = 0; i < n; i++)
	{
		char a, b, c;
		cin >> a >> b >> c;
		int u = id(a), v = id(b), w = id(c);
		// Add triangle of u, v, and w
		add(u, v);
		add(u, w);
		add(v, w);
	}

	// More than 18 disinct letters => no solution
	if (size(ID) > 18)
		fail();

	// Fewer than 18 distinct letters => add arbitrary letters to reach 18.
	for (char c = 'a'; size(ID) < 18; c++)
		id(c);

	array<int, 3> M{};
	if (!rec(0, M))
		fail();
}