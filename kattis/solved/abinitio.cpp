#include <bits/stdc++.h>

using namespace std;

int n, m, q;
vector<vector<bool>> G, H;
bool tr = false;

constexpr int64_t MOD = 1e9 + 7;

int main()
{
	cin >> n >> m >> q;

	G.assign(n, vector<bool>(n, 0));
	H.assign(n, vector<bool>(n, 1));

	const auto conn = [](int a, int b) -> bool
	{
		if (a == b) return false;
		if (tr) swap(a, b);
		return G[a][b];
	};
	const auto vert = []()
	{
		n++;
		for (auto &GG : G)
			GG.push_back(0);
		for (auto &HH : H)
			HH.push_back(1);
		G.push_back(vector<bool>(n, 0));
		H.push_back(vector<bool>(n, 1));
	};
	const auto edge = [](int a, int b)
	{
		if (a == b) return;
		if (tr) swap(a, b);
		G[a][b] = true;
		H[a][b] = false;
	};
	const auto tpse = []()
	{
		tr = !tr;
	};
	const auto cmpl = []()
	{
		G.swap(H);
	};

	while (m--)
	{
		int a, b;
		cin >> a >> b;
		edge(a, b);
	}

	while (q--)
	{
		int t, x, y;
		cin >> t;
		if (t == 1)
		{
			vert();
		}
		else if (t == 2)
		{
			cin >> x >> y;
			edge(x, y);
		}
		else if (t == 3)
		{
			cin >> x;
			cmpl();
			for (y = 0; y < n; y++) edge(x, y);
			tpse();
			for (y = 0; y < n; y++) edge(x, y);
			tpse();
			cmpl();
		}
		else if (t == 4)
		{
			cin >> x >> y;
			cmpl();
			edge(x, y);
			cmpl();
		}
		else if (t == 5)
		{
			tpse();
		}
		else if (t == 6)
		{
			cmpl();
		}
		// for (x = 0; x < n; x++)
		// {
		// 	for (y = 0; y < n; y++)
		// 		cout << conn(x, y);
		// 	cout << '\n';
		// }
		// cout << '\n';
	}

	cout << n << '\n';
	for (int x = 0; x < n; x++)
	{
		int d = 0, h = 0;
		int64_t p7 = 1;
		for (int y = 0; y < n; y++)
			if (conn(x, y))
			{
				d++;
				h = int((h + p7 * y) % MOD);
				p7 = p7 * 7 % MOD;
			}
		cout << d << ' ' << h << '\n';
	}
}