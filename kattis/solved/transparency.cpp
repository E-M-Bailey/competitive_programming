/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/transparency
TAGS: DFA, automata, automaton, deterministic finite automata, deterministic finite automaton, finite automata, finite
automaton, graph, digraph, directed graph, Dijkstra, Dijkstra's algorithm, shortest path EXPLANATION: First, slightly
simplify the original problem. Add a new symbol, $, and treat it as a capital letter. Add two new states, "trash" and
"terminal". All terminal nodes in the original automaton have a $-transition to the new "terminal" node, which becomes
the only terminal state. For all states v and characters c for which a c-transition from state v doesn't exist, add a
c-transition to the "trash" state. Note that this means both the "trash" and the "terminal" nodes have transitions for
every symbol to "trash". This new automaton accepts the same language (set of strings) as the original, except all
accepted strings have a $ appended. However, it only has one terminal node, each accepted string ends in a capital
letter, and for each state v and each character c, there is exactly one c-transition from v. This is not strictly
necessary, but it makes the remaining implementation simpler.

For example, in test case 1, the transitions become:
1,F -> 1
1,A -> 2
2,b -> 1
2,d -> 3
2,F -> 3
3,y -> 4
3,B -> 3
3,$ -> terminal
4,d -> 1
All other combinations -> trash

The main strategy is to construct a new finite state automaton with O(s^2) states. Its alphabet consists of certain
pairs of symbols. More specifically, for all capital letters A (including $), all lowercase letters a and b, and a new
special symbol _, the alphabet contains the pairs AA, ab, a_, and _a as symbols. Assume the number of symbols is O(s)
(since 50 ~ 52). Then, the number of new symbols is O(s^2), so the total number of transitions in the new DFA is O(s^4).

This new automaton will read pairs of strings on the original alphabet, processing the characters in a specific order.
It will accept the strings s and t iff s and t are both accepted by the original automaton, they have the same sequence
of capital letters, and s != t. This new automaton will still have only a single terminal state. Moreover, each
transition will correspond to a small, fixed number of symbols in s and t, called its cost. Treating the new automaton
as a weighted digraph, where states become nodes, transitions become edges, and costs become edge weights, the problem
reduces to finding the shortest path from the node corresponding to the start state to the node corresponding to the
terminal state, or detecting that no such path exists. Paths from the start node to the terminal node correspond to
pairs of strings that are distinct but have the same sequence of capital letters and their lengths correspond to the sum
of these strings' lengths. Thus, the answer is -1 if no such path exists and the length of the shortest such path (-2
due to both strings ending with a $) otherwise.

Any pair of strings we want to accept can be broken into an equal number of (possibly empty) substrings of only
lowercase letters delimited by the same sequence of capital letters. For each pair of corresponding substrings of
lowercase letters, append _ symbols to the shorter one until they have the same length. Then, the DFA will read pairs of
corresponding characters in this string in order. For example, with the strings WabXYcz and gWbXfbYc (slightly different
from the problem's example), the new DFA reads the following pairs of characters:

_g
WW
ab
b_
XX
_f
_b
YY
cc
z_
$$

For now, let's see how to detect whether the two strings are equal, disregarding the requirement that the first DFA
accepts them both. The two strings aren't equal iff any pair has an _ or consists of two distict lowercase characters.
Moreover, we want to enforce that _ characters are added only to the end of the shorter substring of lowercase letters.
This means that after a pair of the form a_ for some lowercase letter a, the only allowed transitions are those of the
form b_ for some lowercase letter b (possibly b = a) until the next transition of the form AA for some capital letter A.
A similar requirement holds for transitions of the form _a.

To check for strings like this, we can use a DFA M with four states:

0: All pairs so far have been equal
1: The last pair was of the form a_
2: The last pair was of the form _a
3: The last pair was of the form aa, ab, or AA and the strings are not equal so far.

Here, A is any capital letter (possibly $) and a and b are any lowercase letters where a != b.
For all such assignments of A, a, and b, M has the following transitions (the numbers in parentheses are costs):

0,aa -> 0 (2)
0,ab -> 3 (2)
0,a_ -> 1 (1)
0,_a -> 2 (1)
0,AA -> 0 (2)

1,a_ -> 1 (1)
1,AA -> 3 (2)

2,_a -> 2 (1)
2,AA -> 3 (2)

3,aa -> 3 (2)
3,ab -> 3 (2)
3,a_ -> 1 (1)
3,_a -> 2 (1)
3,AA -> 3 (2)

In order to enforce the rules on where _'s appear, M has no other transitions (or their costs are infinity). Because the
last pair of characters in accepted strings is always $$, only 3 needs to be a terminal state. The starting state is 0
since two empty strings are equal.

Now, to check that the strings are accepted by the original DFA, take the Cartesian product of two copies of the
original DFA with M. More specifically, construct a DFA where for all states u, v in the original DFA and each state q
in M, there is a state (u,v,q) in the new DFA. Transitions correspond to pairs of symbols, where u follows the first
symbol's transition in the original DFA, v follows the second symbol's transition in the original DFA, and q follows the
transition corresponding to the pair of symbols in M. If no such transition exists in M, the pair of symbols doesn't
correspond to a pair of symbols in the new DFA either. If the first or second symbol in a pair is _, then u or v,
respectively, doesn't change. Transition costs are equal to the corresponding costs in M. The start and terminal states
are the states (u,v,q) where each of u, v, and q are start or terminal states, respectively, in their DFA's (there is
only one of each).

Running the two copies on the first and second characters of each pair corresponds to checking that the first and second
strings, respectively, are accepted by the original DFA (with _'s removed). Running M on the pairs corresponds to
checking that the strings match the other criteria (they have the same sequence of capital letters and they are not
equal even with _'s removed). Taking the Cartesian product of DFA's in this manner corresponds to taking the
intersection of their languages, so this DFA does what we want. Thus, processing it as described earlier yeilds the
answer in O(s^4 log(s)) or even O(s^4) depending on how you calculate shortest paths. END ANNOTATION
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
	int s, p, t;
	cin >> s >> p >> t;
	s += 2;

	const int			   trash = s - 2, terminal = s - 1;
	vector<array<int, 53>> G(s);
	// Gets transition corresponding to a given state and a given symbol.
	const auto tr = [&G](int v, char c) -> int &
	{
		if ('a' <= c && c <= 'z')
			return G[v][c - 'a'];
		else if ('A' <= c && c <= 'Z')
			return G[v][c - 'A' + 26];
		else // c == '$'
			return G[v][52];
	};
	// "All roads lead to trash ..." - Alain de Lille (paraphrased)
	for (int i = 0; i < s; i++)
	{
		for (int c = 'a'; c <= 'z'; c++)
			tr(i, c) = trash;
		for (int c = 'A'; c <= 'Z'; c++)
			tr(i, c) = trash;
		tr(i, '$') = trash;
	}
	// ... except terminal nodes' $-transitions ...
	while (p--)
	{
		int u;
		cin >> u;
		u--;
		tr(u, '$') = terminal;
	}
	// ... and input transitions.
	while (t--)
	{
		int	 u, v;
		char c;
		cin >> u >> c >> v;
		u--;
		v--;
		tr(u, c) = v;
	}

	// The adjacency matrix representation of the Cartesian product DFA as a digraph. Only the minimum-cost transition
	// for each pair of states is kept since we only care about shortest paths.
	int					N = s * s;
	vector<vector<int>> G2(N * 4, vector<int>(N * 4, INT_MAX));
	const auto			add = [&G2](int u, int v, int wt)
	{
		G2[u][v] = min(G2[u][v], wt);
	};
	const auto adds = [s, N, add, &G2](int ui, int uj, int vi, int vj, const array<int, 4> &A, int wt)
	{
		int u = ui * s + uj, v = vi * s + vj;
		for (int i = 0; i < 4; i++)
			if (A[i] >= 0)
				add(u + i * N, v + A[i] * N, wt);
	};

	// The transitions in M of each type (-1 represents a missing transition).
	const array<int, 4> aa{0, -1, -1, 3}, ab{3, -1, -1, 3}, a_{1, 1, -1, 1}, _a{2, -1, 2, 2}, AA{0, 3, 3, 3};

	// Construct the Cartesian product DFA's digraph's adjacency matrix
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
		{
			for (char a = 'a'; a <= 'z'; a++)
			{
				// aa
				adds(i, j, tr(i, a), tr(j, a), aa, 2);
				// ab
				for (char b = 'a'; b <= 'z'; b++)
					if (a != b)
						adds(i, j, tr(i, a), tr(j, b), ab, 2);
				// a_
				adds(i, j, tr(i, a), j, a_, 1);
				// _a
				adds(i, j, i, tr(j, a), _a, 1);
			}
			// AA
			for (char A = 'A'; A <= 'Z'; A++)
				adds(i, j, tr(i, A), tr(j, A), AA, 2);
			adds(i, j, tr(i, '$'), tr(j, '$'), AA, 2);
		}

	// Dijkstra's algorithm: runs in O((V + E)log(V)) = O(s^4 log(s))
	// Extra Credit: shave off the log-factor (make this part run in O(s^4)).
	// Hint: replace the priority queue with something else.
	vector<int>														  D(N * 4, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
	Q.emplace(0, 0);
	while (!Q.empty())
	{
		auto [d, u] = Q.top();
		Q.pop();
		if (D[u] < INT_MAX)
			continue;
		D[u] = d;
		for (int v = 0; v < 4 * N; v++)
		{
			int wt = G2[u][v];
			if (wt < INT_MAX && D[v] == INT_MAX)
				Q.emplace(d + wt, v);
		}
	}

	// Subtract 2 if the path exists to account for the $'s ending both strings.
	int d = D[(s - 1) * s + (s - 1) + 3 * N];
	cout << (d == INT_MAX ? -1 : d - 2);
}
