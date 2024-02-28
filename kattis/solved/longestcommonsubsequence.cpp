/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/longestcommonsubsequence
TAGS: dp, dynamic programming, bitmask, graph, digraph, directed graph, dag, directed acyclic graph, adjacency matrix, matrix, subsequence, string,
permutation
EXPLANATION:

First construct a graph of k vertices represented as an adjacency matrix, where each vertex corresponds to a letter.
In this graph, there is an edge from vertex u to vertex v iff u's letter occurs before v's letter in *every* word in the input.
Note that this is a DAG: a cycle would mean a letter comes both before *and* after another letter in every word, but since
n >= 1 and the words have no repeated letters, this is impossible.

For example, if n = 2, k = 4, and the input words are ABCD and ACBD, the DAG would have edges AB, AC, AD, BD, and CD.
The adjacency matrix would look like:
  ABCD
A 0111
B 0001
C 0001
D 0000

Now, any path in the DAG is a common subsequence, so the problem reduces to finding the length of the longest path in the DAG.
This can be solved in linear time in the number of edges using DFS, but since k is small, the following O(k^3) algorithm also works:

Let S_m be the set of vertices v such that a path of m vertices ending at v exists. Initially, S_1 = V, since all vertices end
the path consisting of just themselves. Then, S_(m + 1) contains the vertices u such that for some v in S_m, the edge u->v exists.
The answer is the maximum m such that S_m is nonempty.

Note that this must terminate after at most k steps since no path with more than k vertices can exist.
Thus, since there are <= k iterations, each of which loops over k values of each of u and v, the runtime is O(k^3).

This can be sped up and simplified by representing each S_m and the adjacency matrix using bitmasks, which I did below.
Depending on how the adjacency matrix is constructed, this takes O(n k^2)
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, k;
	cin >> n >> k;
	int const all = (1 << k) - 1;

	// Adjacency matrix: each entry is a bitmask representing a row.
	vector<int> G(k, all);

	string str;
	while (n--)
	{
		cin >> str;
		// Mask of characters which have not been seen yet in str.
		int rem = all;
		for (char c : str)
		{
			int cur = c - 'A';
			// Current character has been seen
			rem &= ~(1 << cur);
			// Characters which have already been seen in str don't come after cur, so delete the edge from cur to them.
			G[cur] &= rem;
		}
	}

	int ans = 0;
	for (int mask = all; mask; ans++)
	{
		int mask2 = 0;
		// For all vertices v ...
		for (int i = 0; i < k; i++)
			// ... in S_m ...
			if (mask & (1 << i))
				// ... add all vertices u such that v->u exists to S_(m + 1).
				mask2 |= G[i];
		mask = mask2;
	}
	cout << ans;
}
