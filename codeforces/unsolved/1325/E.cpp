#include <bits/stdc++.h>

using namespace std;

// struct dso
// {
// 	int			n, k;
// 	vector<int> P, R;
// 	dso(int n) : n(n), k(n), P(n), R(n)
// 	{
// 		iota(begin(P), end(P), 0);
// 	}
// 	int find(int x)
// 	{
// 		while (x != P[x])
// 			tie(x, P[x]) = pair{P[x], P[P[x]]};
// 		return x;
// 	}
// 	bool onion(int x, int y)
// 	{
// 		x = find(x);
// 		y = find(y);
// 		if (x == y)
// 			return false;
// 		if (R[x] < R[y])
// 			swap(x, y);
// 		R[x] += R[x] == R[y];
// 		P[y] = x;
// 		k--;
// 		return true;
// 	}
// 	vector<vector<int>> comps()
// 	{
// 		vector<vector<int>> ans;
// 		ans.reserve(k);
// 		vector<int> I(n);
// 		for (int x = 0; x < n; x++)
// 			if (x == P[x])
// 			{
// 				I[x] = (int)size(ans);
// 				ans.push_back({x});
// 			}
// 		for (int x = 0; x < n; x++)
// 			if (x != P[x])
// 				ans[I[find(x)]].push_back(x);
// 		return ans;
// 	}
// };

int main()
{
	int HP[1000001]{};
	for (int i = 2; i <= 1000000; i++)
		if (HP[i] == 0)
			for (int j = i; j <= 1000000; j += i)
				HP[j] = i;

	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<int>			   E1;
	vector<pair<int, int>> E2;

	int ans = INT_MAX;

	vector<int> PA;
	while (n--)
	{
		int a;
		cin >> a;
		PA.clear();
		while (a > 1)
		{
			int p = HP[a], pp = 0;
			while (a % p == 0)
			{
				pp++;
				a /= p;
			}
			if (pp % 2)
				PA.push_back(p);
		}

		if (PA.empty())
			ans = 1;
		else if (size(PA) == 1)
			E1.push_back(PA[0]);
		else
			E2.emplace_back(PA[1], PA[0]);
	}

	int n1 = (int)size(E1), n2 = (int)size(E2);

	sort(begin(E1), end(E1));
	E1.erase(unique(begin(E1), end(E1)), end(E1));
	sort(begin(E2), end(E2));
	E2.erase(unique(begin(E2), end(E2)), end(E2));
	if ((int)size(E1) != n1 || (int)size(E2) != n2)
		ans = min(ans, 2);
	n1 = (int)size(E1);
	n2 = (int)size(E2);

	vector<int> P, IP(1000001, -1);
	for (int i = 2; i <= 1000000; i++)
		if (HP[i] == i)
		{
			IP[i] = (int)size(P);
			P.push_back(i);
		}
	for (int &p : E1)
		p = IP[p];
	for (auto &[p, q] : E2)
	{
		p = IP[p];
		q = IP[q];
	}

	int k = (int)size(P);
	int m = int(upper_bound(begin(P), end(P), 1000) - begin(P));

	vector<vector<int>> G(k);
	for (auto [u, v] : E2)
	{
		G[u].push_back(v);
		G[v].push_back(u);
	}

	vector<int> D(k), PR(k);
	queue<int>	Q;

	for (int s = 0; s < m; s++)
	{
		fill(begin(D), end(D), -1);
		fill(begin(PR), end(PR), -1);
		D[s]  = 0;
		PR[s] = s;
		Q.push(s);
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
				if (D[w] < 0)
				{
					D[w]  = D[v] + 1;
					PR[w] = v;
					Q.push(w);
				}
		}

		for (int v = 0; v < k; v++)
			for (int w : G[v])
				if (D[v] >= 0 && PR[v] != w && PR[w] != v)
					ans = min(ans, D[v] + D[w] + 1);

		int d1 = -1, d2 = -1;
		for (int v : E1)
			if (D[v] >= 0)
			{
				if (d1 < 0 || D[v] < d1)
					d2 = exchange(d1, D[v]);
				else if (d2 < 0 || D[v] < d2)
					d2 = D[v];
			}
		if (d2 >= 0)
			ans = min(ans, d1 + d2 + 2);
	}

	cout << (ans == INT_MAX ? -1 : ans);
}
