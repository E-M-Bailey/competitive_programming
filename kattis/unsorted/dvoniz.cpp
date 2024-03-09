#include <bits/stdc++.h>

using namespace std;

struct psegtree
{
	typedef pair<int64_t, int> T;
	static T constexpr UNIT{ 0, 0 };

	constexpr T f(T a, T b)
	{
		return { a.first + b.first, a.second + b.second };
	}

	struct node
	{
		array<int, 2> ch;
		T val;
	};

	int n;
	vector<node> nodes;

	psegtree(int N) : n(N)
	{
		mk();
	}

	T v(int i)
	{
		return i == -1 ? UNIT : nodes[i].val;
	}

	int mk(T val = UNIT)
	{
		int ans = (int)nodes.size();
		nodes.push_back({ {-1, -1}, val });
		return ans;
	}
	int mk(array<int, 2> ch)
	{
		int ans = (int)nodes.size();
		nodes.push_back({ ch, f(v(ch[0]), v(ch[1])) });
		return ans;
	}
	int chld(int i, int d)
	{
		if (nodes[i].ch[d] < 0)
			nodes[i].ch[d] = mk();
		return nodes[i].ch[d];
	}

	int upd(int nl, int nr, int i, int pos, T val)
	{
		//cerr << "  upd " << nl << ' ' << nr << ' ' << i << ' ' << pos << ' ' << val.second << endl;
		if (nr - nl == 1)
			return mk(val);
		int nm = (nl + nr) / 2;
		array<int, 2> ch = nodes[i].ch;
		if (pos < nm)
			ch[0] = upd(nl, nm, chld(i, 0), pos, val);
		else
			ch[1] = upd(nm, nr, chld(i, 1), pos, val);
		return mk(ch);
	}
	int upd(int root, int pos, T val)
	{
		return upd(0, n, root, pos, val);
	}

	T qry(int nl, int nr, int i, int l, int r)
	{
		//cerr << "  qry " << nl << ' ' << nr << ' ' << i << ' ' << l << ' ' << r << endl;
		l = max(l, nl);
		r = min(r, nr);
		if (l >= r || i < 0)
			return UNIT;
		if (l == nl && r == nr)
			return nodes[i].val;
		int nm = (nl + nr) / 2;
		return f(qry(nl, nm, nodes[i].ch[0], l, r), qry(nm, nr, nodes[i].ch[1], l, r));
	}
	T qry(int root, int l, int r)
	{
		//cerr << " qry " << root << ' ' << l << ' ' << r << ' ' <<  qry(0, n, root, l, r).first << endl;
		return qry(0, n, root, l, r);
	}
};

int main()
{
	int n, s;
	cin >> n >> s;
	vector<int> A(n);
	vector<pair<int, int>> B(n);
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
		B[i] = { A[i], i };
	}
	sort(begin(B), end(B));

	psegtree T(n);
	vector<int> roots(n + 1);
	for (int i = 0; i < n; i++)
		roots[i + 1] = T.upd(roots[i], B[i].second, { B[i].first, 1 });

	//cerr << T.qry(roots.back(), 0, n).second;
	/*
	auto const smallsum = [&](int i, int j, int k)
		{
			int lo = 0, hi = n;
			while (lo < hi)
			{
				int t = (lo + hi) / 2;
				auto [_, cnt] = T.qry(roots[t], i, j);
				if (cnt > k)
					hi = t - 1;
				else if (cnt < k)
					lo = t + 1;
				else
					break;
			}
			cerr << " smallsum " << i << ' ' << j << ' ' << k << ' ' << lo << ' ' << hi << ' ' << T.qry(roots[(lo + hi) / 2], i, j).first << ' ' << T.qry(roots[(lo + hi) / 2], i, j).second << endl;
			return T.qry(roots[(lo + hi) / 2], i, j).first;
		};

	auto const nxt = [&](int i, int k, int sum)
		{
			int lo = i + k, hi = n + 1;
			while (lo < hi)
			{
				int j = (lo + hi) / 2;
				if (smallsum(i, j, k) <= sum)
					hi = j;
				else
					lo = j + 1;
			}
			cerr << "nxt " << i << ' ' << k << ' ' << sum << ' ' << lo << endl;
			return lo;
		};
		*/

	for (int i = 0; i < n; i++)
	{
		//if (A[i] > s)
		//{
		//	cout << "0\n";
		//	continue;
		//}
		int lo = 0, hi = n / 2;
		while (lo < hi)
		{
			int k = (lo + hi + 1) / 2;
			if (i + 2 * k > n)
			{
				hi = k - 1;
				continue;
			}
			auto sl = T.qry(roots.back(), i, i + k).first, sr = T.qry(roots.back(), i + k, i + 2 * k).first;
			if (max(sl, sr) > s)
				hi = k - 1;
			else
				lo = k;


			//int j1 = nxt(i + 1, k - 1, s - A[i]);
			//int j2 = nxt(j1, k, s);
			//cerr << lo << ' ' << hi << ' ' << k << endl;
			//if (j2 <= n)
			//	lo = k;
			//else
			//	hi = k - 1;
		}
		cout << lo * 2 << '\n';
	}
}