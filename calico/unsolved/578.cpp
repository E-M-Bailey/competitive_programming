#include <bits/stdc++.h>

using namespace std;

int constexpr B = 100;

int main()
{
	vector<int> HP(10000001);
	for (int i = 2; i <= 10000000; i++)
		if (HP[i] == 0)
			for (int j = i; j <= 10000000; j += i)
				HP[j] = i;

	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> A(n);
	for (auto &AA : A)
	{
		int a;
		cin >> a;
		while (a > 1)
		{
			int p = HP[a];
			a /= p;
			if (AA.empty() || AA.back().first != p)
				AA.emplace_back(p, 0);
			AA.back().second++;
		}
	}

	vector<tuple<int, int, int>> Q(m);
	for (int i = 0; i < m; i++)
	{
		int l, r;
		cin >> l >> r;
		l--;
		Q[i] = {l, r, i};
	}

	sort(begin(Q),
		 end(Q),
		 [&](tuple<int, int, int> a, tuple<int, int, int> b)
		 {
			 return tuple{get<0>(a) / B, get<1>(a), get<0>(a)} < tuple{get<0>(b) / B, get<1>(b), get<0>(b)};
		 });

	vector<int> grundy(m);
	int			cl = 0, cr = 0;
	vector<int> F(10000001);
	int			x = 0;

	auto const add = [&](int i)
	{
		for (auto [p, f] : A[i])
		{
			x ^= F[p];
			x ^= (F[p] += f);
		}
	};
	auto const del = [&](int i)
	{
		for (auto [p, f] : A[i])
		{
			x ^= F[p];
			x ^= (F[p] -= f);
		}
	};

	for (auto [l, r, i] : Q)
	{
		while (cr < r)
			add(cr++);
		while (cl > l)
			add(--cl);
		while (cr > r)
			del(--cr);
		while (cl < l)
			del(cl++);
		grundy[i] = x;
	}

	for (int i = 0; i < m; i++)
		cout << (grundy[i] ? "IGNACIO\n" : "COUSIN\n");
}
