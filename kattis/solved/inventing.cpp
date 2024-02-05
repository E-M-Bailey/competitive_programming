#include <bits/stdc++.h>

using namespace std;

struct dsu
{
	int								   n, k;
	vector<int>						   R;
	mutable vector<int>				   P;
	mutable vector<unordered_set<int>> C;

	dsu(int n) : n(n), k(n), R(n, 0), P(n), C(n)
	{
		iota(begin(P), end(P), 0);
		for (int x = 0; x < n; x++)
			C[x].insert(x);
	}

private:
	void setp(int x, int p) const
	{
		C[P[x]].erase(x);
		C[p].insert(x);
		P[x] = p;
	}

public:
	int find(int x) const
	{
		while (P[x] != x)
		{
			int temp = P[x];
			setp(x, P[P[x]]);
			x = temp;
		}
		return x;
	}

	bool merge(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;

		if (R[y] > R[x])
			swap(x, y);

		setp(y, x);
		if (R[x] == R[y])
			R[x]++;
		k--;
		return true;
	}

	vector<int> elements(int x) const
	{
		x = find(x);
		vector<int> ans;
		vector<int> S;
		S.push_back(x);
		while (!S.empty())
		{
			int y = S.back();
			S.pop_back();
			ans.push_back(y);
			for (int z : C[y])
				if (z != y)
					S.push_back(z);
		}
		return ans;
	}
};

struct edge
{
	int		a, b;
	int64_t w;

	friend bool operator<(const edge &l, const edge &r)
	{
		return l.w < r.w;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<edge> E(n - 1);
		for (edge &e : E)
		{
			cin >> e.a >> e.b >> e.w;
			e.a--;
			e.b--;
		}
		sort(begin(E), end(E));

		dsu D(n);

		int64_t ans = 0;
		for (const edge &e : E)
		{
			size_t A = D.elements(e.a).size(), B = D.elements(e.b).size();
			ans += A * B * (e.w + 1) - 1;
			D.merge(e.a, e.b);
		}
		cout << ans << '\n';
	}
}
