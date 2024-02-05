#include <bits/stdc++.h>

using namespace std;

struct node
{
	int		t, r, p;
	int64_t s;
};

struct p_dso
{
	int					 tim = 0;
	vector<vector<node>> N;

	p_dso(vector<int> const &A) : N(size(A))
	{
		for (int i = 0; i < (int)size(A); i++)
			N[i].push_back({0, 0, i, A[i]});
	}
	node get(int i) const
	{
		return N[i].back();
	}
	node get(int i, int t) const
	{
		return *prev(partition_point(begin(N[i]),
									 end(N[i]),
									 [t](node nd)
									 {
										 return nd.t <= t;
									 }));
	}
	node &get_mut(int i)
	{
		if (node nd = get(i); nd.t != tim)
			N[i].push_back({tim, nd.r, nd.p, nd.s});
		return N[i].back();
	}
	int save()
	{
		return tim++;
	}
	node find(int i) const
	{
		node nd;
		while (nd = get(i), nd.p != i)
			i = nd.p;
		return nd;
	}
	node find(int i, int t) const
	{
		node nd;
		while (nd = get(i, t), nd.p != i)
			i = nd.p;
		return nd;
	}
	bool onion(int i, int j)
	{
		i = find(i).p;
		j = find(j).p;
		if (i == j)
			return false;
		if (get(i).r < get(j).r)
			swap(i, j);
		node &ni = get_mut(i), &nj = get_mut(j);
		nj.p = i;
		ni.r += ni.r == nj.r;
		ni.s += nj.s;
		return true;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<int>					 A(n);
	vector<tuple<int, int, int>> E(m);
	for (int &a : A)
		cin >> a;

	for (auto &[a, u, v] : E)
	{
		cin >> u >> v;
		a = max(A[--u], A[--v]);
	}
	sort(begin(E), end(E));

	p_dso				   D(A);
	vector<pair<int, int>> TS;
	{
		int pr = 0;
		for (auto [a, u, v] : E)
		{
			if (a > pr)
			{
				TS.emplace_back(pr, D.save());
				pr = a;
			}
			D.onion(u, v);
		}
		TS.emplace_back(pr, D.save());
	}

	for (int i = 0; i < n; i++)
	{
		int64_t sum = A[i], prv = 0;
		do
		{
			prv	  = sum;
			int t = prev(partition_point(begin(TS),
										 end(TS),
										 [sum](pair<int, int> pr)
										 {
											 return pr.first <= sum;
										 }))
						->second;
			sum = D.find((int)i, t).s;
		}
		while (sum > prv);
		cout << sum << '\n';
	}
}
