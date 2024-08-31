#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n, m;
	cin >> n >> m;

	vector<int>			C(n);
	vector<vector<int>> A(n, vector<int>(m));
	for (int &c : C)
		cin >> c;
	for (auto &AA : A)
		for (int &a : AA)
			cin >> a;

	int k = n * m;
	int N = k + n;

	vector<vector<pair<int, int>>> G(N);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			G[i * m + j].emplace_back(i + k, C[i]);
			G[i + k].emplace_back(i * m + j, 0);
		}
	}

	vector<int> I(n);
	iota(begin(I), end(I), 0);
	for (int j = 0; j < m; j++)
	{
		sort(begin(I),
			 end(I),
			 [&A, j](int a, int b)
			 {
				 return A[a][j] < A[b][j];
			 });
		for (int i = 1; i < n; i++)
		{
			int a = I[i - 1], b = I[i];
			G[a * m + j].emplace_back(b * m + j, 0);
			G[b * m + j].emplace_back(a * m + j, A[b][j] - A[a][j]);
		}
	}

	int s = k, t = n - 1 + k;

	vector<bool>						 V(N);
	vector<long long>					 D(N, LLONG_MAX);
	priority_queue<pair<long long, int>> Q;
	Q.emplace(0, s);
	while (!Q.empty())
	{
		auto [d, v] = Q.top();
		d			= -d;
		Q.pop();
		if (V[v])
			continue;
		V[v] = true;

		for (auto [w, wt] : G[v])
		{
			if (V[w] || d + wt >= D[w])
				continue;
			D[w] = d + wt;
			Q.emplace(-D[w], w);
		}
	}

	cout << D[t] << '\n';
}
