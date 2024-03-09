#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

uniform_int_distribution<uint64_t> distr(0, numeric_limits<uint64_t>::max());
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

int constexpr NIL = -1;

struct node
{
	uint64_t prior;
	int key, sz, mn, mx, diff;
	array<int, 2> ch;
};

node constexpr UNIT{
	0, 0, 0, INT_MAX / 3, INT_MIN / 3, INT_MAX, {NIL, NIL}
};

struct treap
{
	vector<node> nodes;

	void fix(int nd)
	{
		if (nd == NIL)
			return;
		int key = nodes[nd].key;
		int l = nodes[nd].ch[0], r = nodes[nd].ch[1];
		node const &L = l == NIL ? UNIT : nodes[l];
		node const &R = r == NIL ? UNIT : nodes[r];
		nodes[nd].sz = L.sz + R.sz + 1;
		nodes[nd].mn = min({ L.mn, R.mn, key });
		nodes[nd].mx = max({ L.mx, R.mx, key });
		nodes[nd].diff = min({ L.diff, R.diff, key - L.mx, R.mn - key });
	}

	int mk_node(int key)
	{
		nodes.push_back({ distr(randy), key, 1, key, key, INT_MAX, { NIL, NIL } });
		return int(nodes.size() - 1);
	}

	array<int, 2> split(int root, int key)
	{
		if (root == NIL)
			return { NIL, NIL };
		bool dir = nodes[root].key < key;
		int child = nodes[root].ch[dir];
		nodes[root].ch[dir] = NIL;
		array<int, 2> roots = split(child, key);
		nodes[root].ch[dir] = roots[!dir];
		roots[!dir] = root;
		fix(roots[0]);
		fix(roots[1]);
		return roots;
	}

	int join(array<int, 2> roots)
	{
		if (min(roots[0], roots[1]) == NIL) return max(roots[0], roots[1]);

		bool dir = nodes[roots[1]].prior > nodes[roots[0]].prior;
		int root = roots[!dir];
		roots[!dir] = nodes[root].ch[dir];
		int child = join(roots);
		nodes[root].ch[dir] = child;
		fix(root);
		return root;
	}

	int insert(int root, int key)
	{
		auto [a, c] = split(root, key);
		if (c != NIL && nodes[c].mn == key)
			return join({ a, c });
		int b = mk_node(key);
		return join({ a, join({b, c}) });
	}

	int erase(int root, int key)
	{
		auto [a, bc] = split(root, key);
		if (bc != NIL && nodes[bc].mn != key)
			return join({ a, bc });
		auto [b, c] = split(bc, key + 1);
		return join({ a, c });
	}

	int at_index(int root, int i)
	{
		if (root == NIL)
			return 1000000001;
		auto [l, r] = nodes[root].ch;
		int ls = l == NIL ? 0 : nodes[l].sz;
		if (i < ls)
			return at_index(l, i);
		else if (i == ls)
			return nodes[root].key;
		else
			return at_index(r, i - ls - 1);
	}

	pair<node, int> query(int root, int i, int j)
	{
		int k = at_index(root, i), l = at_index(root, j);
		auto [a, bc] = split(root, k);
		auto [b, c] = split(bc, l);
		auto ans = b == NIL ? UNIT : nodes[b];
		return pair{ ans, join({a, join({b, c})}) };
	}
};

int main()
{
	int Q;
	cin >> Q;
	treap T;
	int root = NIL;
	while (Q--)
	{
		char c;
		cin >> c;
		switch (c)
		{
		case 'I':
		{
			int k;
			cin >> k;
			root = T.insert(root, k);
			break;
		}
		case 'D':
		{
			int k;
			cin >> k;
			root = T.erase(root, k);
			break;
		}
		case 'N':
		{
			int i, j;
			cin >> i >> j;
			j++;
			node ans;
			tie(ans, root) = T.query(root, i, j);
			cout << (i + 1 == j ? -1 : ans.diff) << '\n';
			break;
		}
		case 'X':
		{
			int i, j;
			cin >> i >> j;
			j++;
			node ans;
			tie(ans, root) = T.query(root, i, j);
			cout << (i + 1 == j ? -1 : ans.mx - ans.mn) << '\n';
		}
		}
	}
}