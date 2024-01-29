#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> G;
vector<int> CI;
vector<vector<int>> CC;
vector<int> D;
queue<int> Q;

void dfs(int u, int v)
{
	CI[v] = (int)CC.size() - 1;
	CC.back().push_back(v);
	for (int w : G[v])
		if (w != u)
			dfs(v, w);
}

int diam(int i)
{
	int rem = (int)CC[i].size();
	while (!Q.empty())
		Q.pop();
	for (int v : CC[i])
		if (D[v] == 1)
		{
			D[v] = 0;
			Q.push(v);
		}

	int rad = 0;
	while (rem > 2)
	{
		int ct = (int)Q.size();
		rem -= ct;
		rad++;
		while (ct--)
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
				if (--D[w] == 1)
				{
					D[w] = 0;
					Q.push(w);
				}
		}
	}
	return rad * 2 + (rem == 2);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, l;
	cin >> n >> l;
	G.resize(n);
	CI.resize(n, -1);
	D.resize(n, 0);
	for (int i = 0; i < l; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
		D[a]++;
		D[b]++;
	}
	for (int i = 0; i < n; i++)
		if (CI[i] == -1)
		{
			CC.emplace_back();
			dfs(i, i);
		}
	vector<int> A(CC.size());
	int ans = 0;
	for (int i = 0; i < (int)CC.size(); i++)
	{
		int a = diam(i);
		ans = max(ans, a);
		A[i] = (a + 1) / 2;
	}
	if (A.size() >= 2)
	{
		iter_swap(max_element(begin(A), end(A)), begin(A));
		iter_swap(max_element(begin(A) + 1, end(A)), begin(A) + 1);
		ans = max(ans, A[0] + A[1] + 1);
		if (A.size() >= 3)
			ans = max(ans, A[1] + *max_element(begin(A) + 2, end(A)) + 2);
	}
	cout << ans;
}