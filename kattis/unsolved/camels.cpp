#pragma GCC optimize("Ofast,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;


template<class T>
using os_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Tree
{
	typedef os_set<int> T;

	vector<T> s;
	int n;
	Tree(int N) : s(2 * N), n(N) {}

	int count(int rx, int i)
	{
		//auto lo = s[i].lower_bound(make_pair(lx, INT_MIN));
		auto hi = s[i].lower_bound(rx);
		auto ilo = 0;//lo == s[i].end() ? s[i].size() : s[i].order_of_key(*lo);
		auto ihi = hi == s[i].end() ? s[i].size() : s[i].order_of_key(*hi);
		return (int)(ihi - ilo);
	}

	int query(int rx, int ry)
	{
		int ans = 0, ly = 0;
		for (ly += n, ry += n; ly < ry; ly /= 2, ry /= 2)
		{
			if (ly % 2) ans += count(rx, ly++);
			if (ry % 2) ans += count(rx, --ry);
		}
		return ans;
	}

	void insert_helper(int x, int y, int i)
	{
		s[i].insert(x);
	}

	void insert(int x, int y)
	{
		for (s[y += n].insert(x); y /= 2;)
			s[y].insert(x);
	}
};

/*
struct Node
{

};

bool on_x(const P)*/

int main()
{
	int n;
	cin >> n;
	vector<int> A(n), B(n), C(n);
	for (int &a : A) { cin >> a; a--; }
	for (int &a : B) { cin >> a; a--; }
	for (int &a : C) { cin >> a; a--; }

	vector<int> IA(n);
	for (int i = 0; i < n; i++)
		IA[A[i]] = i;
	for (int &b : B) b = IA[b];
	for (int &c : C) c = IA[c];

	vector<int> IB(n), IC(n);
	for (int i = 0; i < n; i++)
		IB[B[i]] = i;
	for (int i = 0; i < n; i++)
		IC[C[i]] = i;

	Tree tr(n);
	int64_t ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans += tr.query(IB[i], IC[i]);
		tr.insert(IB[i], IC[i]);
	}
	cout << ans;
}