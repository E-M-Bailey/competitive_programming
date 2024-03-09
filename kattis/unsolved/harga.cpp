#include <bits/stdc++.h>

using namespace std;

vector<int>			P;
vector<vector<int>> CH;

struct off_set
{
	int x  = 0;
	int mx = 0;

	unordered_set<int> S;

	bool insert(int y)
	{
		return S.insert(y - x).second;
	}
	template<class F>
	void foreach (F &&f) const
	{
		for (int y : S)
			f(y + x);
	}
	size_t size() const
	{
		return S.size();
	}
	off_set &operator+=(int d)
	{
		x += d;
		return *this;
	}
};

int n, m;

vector<off_set> DP;

template<bool top>
bool dfs(int v)
{
	for (int w : CH[v])
	{
		if (!dfs<0>(w))
			return false;
		DP[w] += 1;
		if (size(DP[w]) > size(DP[v]))
			swap(DP[v], DP[w]);
		DP[w].foreach (
			[v](int x)
			{
				DP[v].insert(x);
			});
	}
	return top || size(DP[v]) == n;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	P.resize(m);
	CH.resize(m);
	DP.resize(m);
	vector<int> X(n);
	for (int i = 0; i < n; i++)
	{
		int &x = X[i];
		cin >> x;
		x--;
		DP[x].insert(i);
	}
	for (int &p : P)
	{
		cin >> p;
		p--;
	}

	bool tail = -1, root = -1;

	vector<int>			CI(m, -1);
	vector<vector<int>> C;
	{
		vector<int> S, I(m, -1);
		for (int i = 0; i < m; i++)
			if (CI[i] < 0)
			{
				for (int ct = 0, j = i; I[j] < 0 && CI[j] < 0; j = P[j], ct++)
				{
					S.push_back(j);
					I[j] = ct;
				}
				int k = P[S.back()];
				if (I[k] >= 0)
				{
					C.push_back(vector(begin(S) + I[k], end(S)));
					for (int j : C.back())
					{
						CI[j] = (int)size(C) - 1;
						I[j]  = -1;
					}
					S.resize(I[k]);
				}
				while (!S.empty())
				{
					CI[S.back()] = CI[k];
					CH[k].push_back(S.back());
					I[k = S.back()] = -1;
				}
				S.clear();
			}
	}

	int k = (int)size(C);
	for (int i = 0; i < m; i++)
		if (size(CH[i]) > 1)
		{
			cout << "-1\n";
			return 0;
		}
	for (auto const &CC : C)
		for (int v : CC)
		{
			if (size(CH[v]) == 1)
			{
				if (root >= 0)
				{
					cout << "-1\n";
					return 0;
				}
				root = v;
			}
		}

	if (root >= 0)
	{
		tail = root;
		while (!CH[tail].empty())
			tail = CH[tail][0];

		if (k > 1)
		{
			cout << "-1\n";
			return 0;
		}
		for (int x : X)
			if (x != tail)
			{
				cout << "-1\n";
				return 0;
			}
		cout << m;
		return 0;
	}

	if (tail != root)
	{
		bool good = true;
		for (int i = 0; i < n; i++)
			good &= X[i] == tail;
		if (good)
			for (int i = 0; i < n; i++)
				cout << m << ' ';
		else
			cout << "-1\n";
		return 0;
	}

	vector<int> IDX(m);
	for (int i = 0; i < m; i++)
		IDX[CC[0][i]] = i;
	for (int &x : X)
		x = IDX[x];
}
